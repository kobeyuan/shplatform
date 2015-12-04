#include "KinectShow.h"


KinectShow::KinectShow(QWidget *parent):  m_para(global_paraMgr.getKinectParameterSet())/*,
	                                      glDrawer(global_paraMgr.getDrawerParameterSet()),
										  m_dataMgr(global_paraMgr.getDataParameterSet())*/
	                                               		  
{
	cout<<"construct kinect class"<<endl;	
	//m_area = (GLArea*)parent;
	m_pointCloud.clear();
}
KinectShow::~KinectShow(void)
{
	//m_StreamDepth.destroy();
	//m_device.close();
	//openni::OpenNI::shutdown();

}
void KinectShow::openKinect()
{
	// 初始化OpenNI环境
	OpenNI::initialize();
	// 打开设备
	m_device.open(ANY_DEVICE );

	m_StreamDepth.create(m_device, SENSOR_DEPTH );
	m_StreamColor.create(m_device, SENSOR_COLOR );

	// 设置深度图像视频模式
	// 分辨率大小
	m_ModeDepth.setResolution( 640, 480 );
	// 每秒30帧
	m_ModeDepth.setFps( 30 );
	// 像素格式
	m_ModeDepth.setPixelFormat( PIXEL_FORMAT_DEPTH_1_MM );
	m_StreamDepth.setVideoMode(m_ModeDepth);

	//设置彩色图像视频模式
	m_ModeColor.setResolution(640,480);
	m_ModeColor.setFps(30);
	m_ModeColor.setPixelFormat(PIXEL_FORMAT_RGB888);
	m_StreamColor.setVideoMode(m_ModeColor);


	//代开对齐的功能两次,与"convertDepthToColor"函数重复.

	//if( m_device.isImageRegistrationModeSupported(
	//	IMAGE_REGISTRATION_DEPTH_TO_COLOR ) )
	//{
	//	m_device.setImageRegistrationMode( IMAGE_REGISTRATION_DEPTH_TO_COLOR );
	//}

	// 打开深度和图像数据流
	m_StreamDepth.start();
	m_StreamColor.start();

	// 创建OpenCV图像窗口
	namedWindow( "深度图像",  CV_WINDOW_AUTOSIZE );
	namedWindow( "彩色图像",  CV_WINDOW_AUTOSIZE );

	int iMaxDepth = m_StreamDepth.getMaxPixelValue();
	m_isGenrPCloud = true;
	m_frameNum = 0;
	while(true)
	{
		m_StreamDepth.readFrame(&m_frameDepth);
		m_StreamColor.readFrame(&m_frameColor);
		// 将深度数据转换成OpenCV格式
		const cv::Mat mImageDepth(m_frameDepth.getHeight(), m_frameDepth.getWidth(), CV_16UC1, (void*)m_frameDepth.getData());
		// 为了让深度图像显示的更加明显一些，将CV_16UC1 ==> CV_8U格式
		cv::Mat mScaledDepth;
		mImageDepth.convertTo( mScaledDepth, CV_8U, 255.0 / iMaxDepth );
		// 显示出深度图像
		cv::imshow( "深度图像", mScaledDepth );

		///用于转化点云 depth
		const openni::DepthPixel* pDepthRow = (const openni::DepthPixel*)m_frameDepth.getData();
	    ///
		// 同样的将彩色图像数据转化成OpenCV格式
		const cv::Mat mImageRGB(m_frameColor.getHeight(), m_frameColor.getWidth(), CV_8UC3, (void*)m_frameColor.getData());
		// 首先将RGB格式转换为BGR格式
		cv::Mat cImageBGR;
		cv::cvtColor( mImageRGB, cImageBGR, CV_RGB2BGR );
		// 然后显示彩色图像
		cv::imshow( "彩色图像", cImageBGR );
		///用于转化点云 color
		const openni::RGB888Pixel* pImageRow = (const openni::RGB888Pixel*)m_frameColor.getData();
		///
		if (m_isGenrPCloud && m_frameNum == 40 )
		{
		    //imwrite("hand_back.jpg",cImageBGR);
			//m_pointCloud.resize(0);
			generatePointCloud(m_StreamColor,m_StreamDepth,pDepthRow,pImageRow,m_pointCloud);
			//m_area->initAfterOpenFile();
			//m_area->updateGL();
			break;
			//std::stringstream ss; //save point file
			//ss << m_frameNum;
			//std::string Numstr = ss.str();
			//std::string fileName = Numstr + ".xyzrgb"; 
			//std::ofstream outFrame(fileName.c_str());
			//for (int np = 0; np < m_pointCloud.size(); np++)
			//{
			//	SColorPoint3D curP(m_pointCloud.at(np));
			//	outFrame<<curP.X<<" "<<curP.Y<<" "<<curP.Z<<" "<<curP.R<<" "<<curP.G<<" "<<curP.B<<std::endl;
			//}
			//outFrame.close();
			//cout<<"第1000个点坐标"<<m_pointCloud.at(1000).X<<"  "<<m_pointCloud.at(1000).Y<<"  "<<m_pointCloud.at(1000).Z<<endl;
			//m_isGenrPCloud = false;
		}
		m_frameNum ++;
		// 终止快捷键
		if( cv::waitKey(1) == 'q')
			break;
	}

	// 关闭数据流
	m_StreamDepth.destroy();
	m_StreamColor.destroy();
	// 关闭设备
	m_device.close();
	// 最后关闭OpenNI
	openni::OpenNI::shutdown();
}
void KinectShow::generatePointCloud(openni::VideoStream& colorStream,
	openni::VideoStream& depthStream,
	const openni::DepthPixel* pDepth,
	const openni::RGB888Pixel* pImage,
	std::vector<SColorPoint3D>& vPointCloud)
{
	// 1. number of point is the number of 2D image pixel
	openni::VideoFrameRef curDetphFrame ;
	depthStream.readFrame(&curDetphFrame); 
	unsigned int uPointNum = curDetphFrame.getWidth() * curDetphFrame.getHeight();

	// 2. build the data structure for convert
	float* p3DPointSet = new float[uPointNum*3];
	int* colorID = new int[uPointNum];
	unsigned int x,y, idxShift, idx;
	//unsigned totalVer = 0;
	for( y = 0; y < curDetphFrame.getHeight(); ++ y)
	{
		idxShift = y * curDetphFrame.getWidth();
		for( x = 0; x < curDetphFrame.getWidth(); ++ x)
		{
			idx = (idxShift + x);
			float fX, fY, fZ;  
			//转化函数付出的代价很高，要尽可能的先处理图像再把像素转化成三维点
			if (pDepth[idx] < 500 || pDepth[idx] > 1000) continue;
			openni::CoordinateConverter::convertDepthToWorld( depthStream, x, y, pDepth[idx], &fX, &fY, &fZ );
// 			p3DPointSet[idx*3+0] = fX;
// 			p3DPointSet[idx*3+1] = fY;
// 			p3DPointSet[idx*3+2] = fZ;
			int pcx, pcy;
			openni::CoordinateConverter::convertDepthToColor(depthStream, colorStream, x, y, pDepth[idx], &pcx, &pcy);
			colorID[idx] = pcy*curDetphFrame.getWidth() + pcx; //need to change for the color frame
			//建立点云
			openni::RGB888Pixel color_ = pImage[colorID[idx]];
			vPointCloud.push_back( SColorPoint3D(fX, fY,fZ, color_.r,color_.g,color_.b/*pImage[colorID[i]]*/ ) );
			//totalVer ++;
		}
	}
// 	// 4. build point cloud
// 	std::vector<SColorPoint3D>().swap(vPointCloud);  
// 
// 	for(unsigned int i = 0; i < totalVer/*uPointNum*/; ++ i )
// 	{
// 		// skip the depth 0 points
// 		//if( p3DPointSet[3*i+2] == 0 )
// 		//	continue;
// 
// 		//剔除背景点，对每个点都进行了操作
// 		//if( p3DPointSet[3*i+2] == 0 || p3DPointSet[3*i+2] > 1500)
// 		//	continue;
// 
// 		openni::RGB888Pixel color_ = pImage[colorID[i]];
// 		vPointCloud.push_back( SColorPoint3D( p3DPointSet[3*i+0], p3DPointSet[3*i+1], p3DPointSet[3*i+2], color_.r,color_.g,color_.b/*pImage[colorID[i]]*/ ) );
// 	}
	delete[] p3DPointSet;
	delete[] colorID;
}
void KinectShow::GenerPointCloud(bool isGener)
{
	//if (isGener)
	//{
	//	generatePointCloud(m_StreamColor,m_StreamDepth,)
	//}
}
void KinectShow::initializeGL()
{
}
void KinectShow::resizeGL(int w, int h)
{
}
void KinectShow::paintGL()
{
}
// void KinectShow::reconstructMe()
// {
// 	// Create a new context
// 	reme_context_t c;
// 	reme_context_create(&c);
// 	reme_context_set_log_callback(c, reme_default_log_callback, 0);
// 	// Compile for OpenCL device using defaults
// 	reme_context_compile(c);
// 	// Create a new volume
// 	reme_volume_t v;
// 	reme_volume_create(c, &v);
// 	// Create a new sensor. Tries multiple backends using default
// 	// sensor configurations, returns the first working one. By default
// 	// each sensor works on the first volume created.
// 	reme_sensor_t s;
// 	reme_sensor_create(c, "openni;mskinect;file", true, &s);
// 	reme_sensor_open(c, s);
// 	reme_sensor_set_prescan_position(c, s, REME_SENSOR_POSITION_INFRONT);
// 	// For debugging purposes open a viewer for tracking the reconstruction process.
// 	reme_viewer_t viewer;
// 	reme_viewer_create_image(c, "This is ReconstructMe SDK", &viewer);
// 	reme_image_t volume, aux;
// 	reme_image_create(c, &volume);
// 	reme_image_create(c, &aux);
// 	reme_viewer_add_image(c, viewer, aux);
// 	reme_viewer_add_image(c, viewer, volume);
// 	// Reconstruct until viewer is closed, or grabbing fails. Note that
// 	// aborting reconstruction just because a single grab failed is not good stlye.
// 	// You should allow for multiple grab attempts.
// 	printf("Starting reconstruction. Close the viewer window to stop.\n");
// 	bool viewer_done = false;
// 	while (!viewer_done && REME_SUCCESS(reme_sensor_grab(c, s))) 
// 	{
// 		// Prepare image and depth data
// 		reme_sensor_prepare_images(c, s);
// 		// Try to determine updated sensor position.
// 		// On succes, update volume, otherwise move to a recovery position
// 		// and wait for the tracking to start again.
// 		if (REME_SUCCESS(reme_sensor_track_position(c, s))) 
// 		{
// 			// Update volume with depth data from the
// 			// current sensor perspective
// 			reme_sensor_update_volume(c, s);
// 		}
// 		// Update the viewer
// 		reme_sensor_get_image(c, s, REME_IMAGE_AUX, aux);
// 		reme_sensor_get_image(c, s, REME_IMAGE_VOLUME, volume);
// 		reme_viewer_update(c, viewer);
// 		reme_viewer_is_closed(c, viewer, &viewer_done);
// 	}
// 	// Close and destroy the sensor, it is not needed anymore
// 	reme_sensor_close(c, s);
// 	reme_sensor_destroy(c, &s);
// 	// Create a new surface
// 	reme_surface_t m;
// 	reme_surface_create(c, &m);
// 	reme_surface_generate(c, m, v);
// 	reme_surface_save_to_file(c, m, "MeCons.ply");
// 	// Visualize resulting surface
// 	reme_viewer_t viewer_surface;
// 	reme_viewer_create_surface(c, m, "This is ReconstructMeSDK", &viewer_surface);
// 	reme_viewer_wait(c, viewer_surface);
// 	reme_surface_destroy(c, &m);
// 	// Print pending errors
// 	reme_context_print_errors(c);
// 	// Make sure to release all memory acquired
// 	reme_context_destroy(&c);
// }



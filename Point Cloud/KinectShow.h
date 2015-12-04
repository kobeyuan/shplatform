#pragma once
#include "gl/glew.h"
#include <QWidget>
#include <QColor>
#include <QImage>
#include <QPoint>
#include <QtGui>
#include <QtOpenGL/QGLWidget>
#include<QString>
//
//#include <wrap/gl/trimesh.h>
//#include <wrap/gui/trackball.h>
#include <vcg\space\point3.h>
//#include <wrap/io_trimesh/import.h>
//#include <wrap/io_trimesh/export.h>
#include <iostream>
//
// #include "Algorithm/NormalSmoother.h"
 #include "DataMgr.h"
// #include "GLDrawer.h"
// #include "CMesh.h"
 #include "ParameterMgr.h"
// #include "Algorithm/PointCloudAlgorithm.h"
// #include "Algorithm/WLOP.h"
// #include "Algorithm/Skeletonization.h"
// #include "Algorithm/Upsampler.h"

//
#include <OpenNI.h>

#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

//#include <reconstructmesdk/reme.h>
//
//#include "GLArea.h"
using std::cout;
using std::endl;
using vcg::Point3f;
using namespace vcg;
using std::vector;
//
using namespace  cv;
using namespace openni;

class KinectShow :public QGLWidget
{
public:
	Q_OBJECT
public:
	KinectShow(QWidget *parent = 0);
	~KinectShow(void);

	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL(); 
	//void updateUI(){emit needUpdateStatus();}
public:
	void openKinect();
	void GenerPointCloud(bool isGener);
	void generatePointCloud(openni::VideoStream& colorStream,
		                    openni::VideoStream& depthStream,
							const openni::DepthPixel* pDepth,
							const openni::RGB888Pixel* pImage,
							std::vector<SColorPoint3D>& vPointCloud);
public:
	//void reconstructMe();
		
public:
	Device        m_device;
	VideoStream   m_StreamDepth;//深度数据流
	VideoStream   m_StreamColor;//彩色数据流
	VideoFrameRef m_frameDepth;//保存深度数据流
	VideoFrameRef m_frameColor;//保存深度数据流

	VideoMode m_ModeDepth;//设置深度图像视频模式m_mod
	VideoMode m_ModeColor;
	int m_frameNum;
public:	
	RichParameterSet* m_para;
	//GLDrawer glDrawer;
    //DataMgr m_dataMgr;
	std::vector<SColorPoint3D> m_pointCloud;
	bool m_isGenrPCloud;
public:
	//GLArea* m_area;

};
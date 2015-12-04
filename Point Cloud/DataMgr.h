#pragma once
#include "cmesh.h"
#include "Parameter.h"
#include "GlobalFunction.h"
#include "Algorithm/Skeleton.h"



#include <wrap/io_trimesh/import.h>
#include <wrap/io_trimesh/export.h>

#include <sstream>
#include <fstream>
#include <set>
//
//#include <OpenNI.h>

using namespace vcg;
using namespace std;
using namespace tri;

struct SColorPoint3D
{
	float  X;
	float  Y;
	float  Z;
	float  R;
	float  G;
	float  B;

	SColorPoint3D( float x, float y, float z,float r, float g, float b/*openni::RGB888Pixel color*/ )
	{
		X = x;
		Y = y;
		Z = z;
		R = r / 255;
		G = g / 255;
		B = b / 255;
	}
};

class DataMgr
{
public:
	DataMgr(RichParameterSet* _para);
	~DataMgr(void);

	void loadPlyToOriginal(QString fileName);
	void loadPlyToSample(QString fileName);
	void savePly(QString fileName, CMesh& mesh);
	void loadImage(QString fileName);
    void loadXYZN(QString fileName);

	//载入点云数据
	void loadXYZRGB(const vector<SColorPoint3D> & pCloudFKnt);
	void setSample(CMesh & samp);
	//
	bool isSamplesEmpty();
	bool isOriginalEmpty();
    bool isSkeletonEmpty();

	CMesh* getCurrentSamples();
	CMesh* getCurrentOriginal();
	Skeleton* getCurrentSkeleton();

	void recomputeBox();
	double getInitRadiuse();

	void downSamplesByNum(bool use_random_downsample = true);
	void subSamples();

	void normalizeROSA_Mesh(CMesh& mesh);
	Box3f normalizeAllMesh();

	void eraseRemovedSamples();
	void clearData();
	void recomputeQuad();

	void loadSkeletonFromSkel(QString fileName);
	void saveSkeletonAsSkel(QString fileName);


private:
	void clearCMesh(CMesh& mesh);

public:
	CMesh original;
	CMesh samples;
	Skeleton skeleton;
	//cv::Mat image;

	RichParameterSet* para;
	double init_radius;
	QString curr_file_name;
};


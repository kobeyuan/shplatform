#pragma once
#include "Parameter.h"
#include "CMesh.h"

class ParameterMgr
{
public:
	ParameterMgr(void);
	~ParameterMgr(void);
	RichParameterSet* getDataParameterSet(){ return &data; }
	RichParameterSet* getDrawerParameterSet(){ return &drawer; }
	RichParameterSet* getGlareaParameterSet(){ return &glarea; }
	RichParameterSet* getWLopParameterSet(){ return &wLop; }
	RichParameterSet* getSkeletonParameterSet(){ return &skeleton; }	
	RichParameterSet* getNormalSmootherParameterSet(){ return &norSmooth; }
	RichParameterSet* getUpsamplingParameterSet(){ return &upsampling; }
	//
	RichParameterSet* getKinectParameterSet(){ return &m_kinect; }
	RichParameterSet* getRigisterParameterSet(){return & m_rigister;}
	//

	void setGlobalParameter(QString paraName,Value& val);
	typedef enum {GLAREA, DATA, DRAWER, WLOP, NOR_SMOOTH, SKELETON, UPSAMPLING,KINECT}ParaType;

private:
	void initDataMgrParameter();
	void initDrawerParameter();
	void initGlareaParameter();
	void initWLopParameter();
	void initSkeletonParameter();
	void initNormalSmootherParameter();
	void initUpsamplingParameter();
	//
	void initKinectParameter();
	void initRigisterParameter();
	//
public:
	RichParameterSet glarea;
	RichParameterSet data;
	RichParameterSet drawer;
	RichParameterSet wLop;
	RichParameterSet norSmooth;
	RichParameterSet skeleton;
	RichParameterSet upsampling;
	//
	RichParameterSet m_kinect;
	RichParameterSet m_rigister;
	//

private:
	static int init_time;
	double grid_r;
};

extern ParameterMgr global_paraMgr;
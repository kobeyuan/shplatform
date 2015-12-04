#pragma  once
#include "GlobalFunction.h"
#include "Algorithm/PointCloudAlgorithm.h"
#include "DataMgr.h"
#include "Parameter.h"
#include "SparseICP.h"

class Rigister : public PointCloudAlgorithm
{
public:
	Rigister(RichParameterSet * para);
	~Rigister();

public:
	void run();
	void setInput(DataMgr * pData);
	RichParameterSet * getParameterSet(){return m_para;}
	void setParameterSet(RichParameterSet* _para){m_para = _para;}
	void clear(){m_sourse = NULL;m_target = NULL;};

private:
	void input(CMesh * _samples,CMesh * _original);
	void runSparseICP();

private:
	RichParameterSet * m_para;

private:
	CMesh * m_sourse;
	CMesh * m_target;

private:
	int m_iterNum;
	Timer m_time;
};
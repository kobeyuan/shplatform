#include "Register.h"
Rigister::Rigister(RichParameterSet * para)
{
	cout<<"construct Rigisrer class"<<endl;
	m_para = para;
	m_sourse = NULL;
	m_target = NULL;
	m_iterNum = 0;
}
Rigister::~Rigister()
{
   cout<<"Rigister destroy!"<<endl;
}
void Rigister::setInput(DataMgr * pData)
{
	if (!pData->isSamplesEmpty() && !pData->isOriginalEmpty())
	{
		m_sourse = pData->getCurrentOriginal();
		m_target = pData->getCurrentSamples();
	}
	else
	{
		cout<<"The input clouds are empty!"<<endl;
		return;
	}
}
void Rigister::run()
{
	runSparseICP();
	//cout<<"do nothing"<<endl;
}
void Rigister::runSparseICP()
{
	MatrixXX SrCloud;
	MatrixXX TgCloud;
    MatrixXX verterMap;//点之间的对应

	int srVerNum = m_sourse->vert.size(); 
	int tgVerNum = m_target->vert.size();
	SrCloud.resize(3,srVerNum);
	TgCloud.resize(3,tgVerNum);
	verterMap.resize(1,srVerNum);

	for(int i = 0; i < srVerNum; i++)
	{
		CVertex& v = m_sourse->vert[i];
		SrCloud(0,i) = v.P()[0];
		SrCloud(1,i) = v.P()[1];
		SrCloud(2,i) = v.P()[2];
	}

	for(int i = 0; i < tgVerNum; i++)
	{
		CVertex& v = m_target->vert[i];
		TgCloud(0,i) = v.P()[0];
		TgCloud(1,i) = v.P()[1];
		TgCloud(2,i) = v.P()[2];
	}
	//cout<<"before ,first point "<<SrCloud.col(0)<<endl;
	SparseICP::SICP::Parameters pa;
	SparseICP::SICP::point_to_point(SrCloud,TgCloud,verterMap,pa);

	//update the sourse coor
	for(int i = 0; i < srVerNum; i++)
	{
		CVertex& v = m_sourse->vert[i];
		v.P()[0] = SrCloud(0,i);
		v.P()[1] = SrCloud(1,i);
		v.P()[2] = SrCloud(2,i);
	}
	//cout<<"after,first point "<<SrCloud.col(0)<<endl;

}

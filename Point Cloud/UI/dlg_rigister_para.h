#pragma  once

#include <QtGui>
#include <QtGui/QFrame>
#include <QtGui/QWidget>
#include <iostream>

//#include "ui_para_wlop.h"
#include "..//GeneratedFiles//ui_para_rigister.h"//�Լ�����Ľ���
#include "ParameterMgr.h"
#include "glarea.h"
#include "calculationthread.h"

using namespace std;
class RigisterParaDlg : public QFrame
{
	Q_OBJECT
public:
	RigisterParaDlg(QWidget *p,ParameterMgr * _paras,GLArea * _area);
	~RigisterParaDlg();
	void initConnects();
	void setFrameConents();

private slots:
	bool initWidgets();
	void getTestUiValues(double _val);
	void getInput(double _val);
	void playMap();
private:
	Ui::rigister * ui;
	ParameterMgr * m_paras;//�������---������������
	GLArea * m_area;       //�����㷨
	CalculationThread m_rgtCalThed;
};
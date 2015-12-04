#pragma  once

#include <QtGui>
#include <QtGui/QFrame>
#include <QtGui/QWidget>
#include <iostream>

//#include "ui_para_wlop.h"
#include "..//GeneratedFiles//ui_para_rigister.h"//自己定义的界面
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
	ParameterMgr * m_paras;//管理参数---被界面的类管理
	GLArea * m_area;       //管理算法
	CalculationThread m_rgtCalThed;
};
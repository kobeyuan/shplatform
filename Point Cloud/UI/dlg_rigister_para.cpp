#include "UI/dlg_rigister_para.h"

RigisterParaDlg::RigisterParaDlg(QWidget *p,ParameterMgr * _paras,GLArea * _area)
{
	ui = new Ui::rigister;
	RigisterParaDlg::ui->setupUi(this);
	m_area = _area;
	m_paras = _paras;

	if (!initWidgets())
	{
		cerr<<"RigisterParaDlg::initwidgets failed.";
		return;
	}
	initConnects();

}
RigisterParaDlg::~RigisterParaDlg()
{
	delete ui;
	ui = NULL;
	
	m_area = NULL;
	m_paras = NULL;

}
void RigisterParaDlg::initConnects()
{
	connect(ui->doubleSpinBox,SIGNAL(valueChanged(double)),this,SLOT(getInput(double)));
	connect(ui->SparseICP,SIGNAL(clicked()),this,SLOT(playMap()));
}
void RigisterParaDlg::getTestUiValues(double _val)
{
	m_paras->m_rigister.setValue("test ui",DoubleValue(_val));
}
void RigisterParaDlg::getInput(double _val)
{
	m_paras->m_rigister.setValue("input",DoubleValue(_val));
}
bool RigisterParaDlg::initWidgets()
{
	ui->doubleSpinBox->setValue(m_paras->m_rigister.getDouble("input"));
	return true;
}
void RigisterParaDlg::playMap()
{
	m_area->runCloudMap();
}

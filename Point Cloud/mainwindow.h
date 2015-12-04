#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include "Algorithm/normal_extrapolation.h"
#include "ui_mainwindow.h"
#include "GLArea.h"
#include "UI/std_para_dlg.h"
#include "UI/dlg_wlop_para.h"
#include "ParameterMgr.h"
#include "calculationthread.h"

// 获得输入数据
//#include"KinectShow.h"
//

//MainWindow类主要用来消息响应
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
	~MainWindow();
private:
	void init();
	void initWidgets();
	void initConnect();
	void iniStatusBar();
	void createActionGroups();


private slots:
	void updateStatusBar();
	void dropEvent ( QDropEvent * event );
	void dragEnterEvent(QDragEnterEvent *);

	void openFile();
	void saveFile();
	void downSample();
	void subSample();
	void normalizeData();
	void clearData();
	void saveSnapshot();
	void openImage();
	void saveView();
	void saveSkel();
    void getQianSample();
	//
	void displayKinect();
	//

	void showWLopDlg();
	void showNormalDlg();
	void showSkeletonDlg();
	void showUpsampleDlg();
	//
	void showRigisterDlg();
	//
	void autoPlaySkeleton();
	void stepPlaySkeleton();
	void jumpPlaySkeleton();
	void initialSampling();
	void setStop();

	void removePickPoints();

	

private slots:
	void runWLop();

public slots:
	void runPCA_Normal();
	void reorientateNormal();

private slots:
	void lightOnOff(bool _val);
	void showOriginal(bool _val);
	void showSamples(bool _val);
	void showNormals(bool _val);
    void showSkeleton(bool _val);
	void cullPoints(bool _val);
	void showNormalColor(bool _val);
	void showNeighborhoodBall(bool _val);
	void showAllNeighborhoodBall(bool _val);
	void showIndividualColor(bool _val);
	void setSnapshotEachIteration(bool _val);
	void setNoSnapshotWithRadius(bool _val);
    void showColorfulBranches(bool _val);

	void setSmapleType(QAction * action);
	void setOriginalType(QAction * action);


private slots:
	void sampleColor();
	void originalColor();
	void backGroundColor();
	void normalColor();
	void featureColor();

	void ambientColor();
	void diffuseColor();
	void specularColor();
	void recomputeQuad();

private:
	GLArea* area;
	CalculationThread calculation_thread;
	
	//------------
	//KinectShow * m_kinect;
	//
	QString strTitle;
	QLabel * original_size_label;
	QLabel * sample_size_lable;
	QLabel * downSample_num_label;
	QLabel * radius_label;
	QLabel * error_label;
    QLabel * iteration_label;

	ParameterMgr * paras;
	StdParaDlg * paraDlg_Skeleton;
	StdParaDlg * paraDlg_Upsample;//QDockWidget类提供了一个特殊的窗口部件，
	StdParaDlg * paraDlg_WLOP;//它可以是被锁在QMainWindow窗口内部或者是作为顶级窗口悬浮在桌面上。
	StdParaDlg * paraDlg_Normal;  
	//
	StdParaDlg * m_paraDlgRigister;//ICP参数设置窗口

	QActionGroup * sample_draw_type;  //QActionGroup的作用就是将多个相似的动作组合在一起。这里我们假设要对一组文字作对齐操作，。
	QActionGroup * original_draw_type; //有Left Align, Right Align, Just Align, Center Align四个动作

private:
	Ui::mainwindowClass ui;
};

#endif // MAINWINDOW_H

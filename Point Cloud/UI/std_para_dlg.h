#pragma once

#include <iostream>
#include <QDialog>
#include <QtGui>
#include <QtGui/QFrame>
#include <QtGui/QWidget>
#include <QtGui/QDockWidget>
#include <QtGui/QGridLayout>


#include "ParameterMgr.h"
#include "UI/dlg_wlop_para.h"
#include "UI/dlg_normal_para.h"
#include "UI/dlg_skeleton_para.h"
#include "UI/dlg_upsampling_para.h"
//
#include "UI/dlg_rigister_para.h"
//
#include "glarea.h"

using namespace std;

class StdParaDlg : public QDockWidget
{
	Q_OBJECT
	public:
		StdParaDlg(ParameterMgr* _paras, GLArea * _area, QWidget* parent = 0);
		~StdParaDlg();

		bool showWlopParaDialog();
		bool showNormalParaDlg();
		bool showSkeletonParaDlg();
		bool showUpsamplingParaDlg();
		//
		bool showRigisterParaDlg();
		//

	private:
		void init();
		void createFrame();
		void loadWlopFrame();
		void loadNormalFrame();
		void loadSkeletonFrame();
		void loadUpsamplingFrame();
		//
		void loadRigisterFrame();
		//
	private slots:
		 void closeClick();
		 
	private:
		WlopParaDlg * para_wlop;
		NormalParaDlg * para_normal;
		SkeletonParaDlg* para_skeleton;
		UpsamplingParaDlg* para_upsampling;
		//
		RigisterParaDlg * m_para_rigister;
		 //
		ParameterMgr * paras;

		QFrame * mainFrame;
		GLArea * gla;
};

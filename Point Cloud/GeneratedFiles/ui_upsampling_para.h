/********************************************************************************
** Form generated from reading UI file 'upsampling_para.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPSAMPLING_PARA_H
#define UI_UPSAMPLING_PARA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Upsampling_para
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    QPushButton *pushButton_Projection;
    QCheckBox *using_threshol_process;
    QPushButton *apply_add_point;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QDoubleSpinBox *sigma;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_7;
    QSpinBox *add_num;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_8;
    QDoubleSpinBox *threshold;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_12;
    QDoubleSpinBox *edge_paramete;
    QWidget *layoutWidget4;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QDoubleSpinBox *radius;
    QWidget *tab_2;
    QDoubleSpinBox *video_speed;
    QLabel *label_70;
    QDoubleSpinBox *begin_index;
    QPushButton *pushButton_play_video;
    QLabel *label_69;
    QLabel *label_64;
    QDoubleSpinBox *end_index;
    QLabel *label_62;
    QDoubleSpinBox *wlop_snapshot_index;
    QDoubleSpinBox *wlop_snapshot_resolution;
    QLabel *label_63;

    void setupUi(QWidget *Upsampling_para)
    {
        if (Upsampling_para->objectName().isEmpty())
            Upsampling_para->setObjectName(QStringLiteral("Upsampling_para"));
        Upsampling_para->resize(263, 521);
        tabWidget = new QTabWidget(Upsampling_para);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 241, 481));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        pushButton_Projection = new QPushButton(tab);
        pushButton_Projection->setObjectName(QStringLiteral("pushButton_Projection"));
        pushButton_Projection->setGeometry(QRect(40, 250, 141, 23));
        using_threshol_process = new QCheckBox(tab);
        using_threshol_process->setObjectName(QStringLiteral("using_threshol_process"));
        using_threshol_process->setGeometry(QRect(12, 96, 161, 16));
        apply_add_point = new QPushButton(tab);
        apply_add_point->setObjectName(QStringLiteral("apply_add_point"));
        apply_add_point->setGeometry(QRect(50, 200, 121, 31));
        layoutWidget = new QWidget(tab);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(13, 31, 201, 22));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_2->addWidget(label_3);

        sigma = new QDoubleSpinBox(layoutWidget);
        sigma->setObjectName(QStringLiteral("sigma"));
        sigma->setDecimals(2);
        sigma->setMaximum(180);
        sigma->setValue(30);

        horizontalLayout_2->addWidget(sigma);

        layoutWidget1 = new QWidget(tab);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 160, 201, 22));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_7 = new QLabel(layoutWidget1);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_5->addWidget(label_7);

        add_num = new QSpinBox(layoutWidget1);
        add_num->setObjectName(QStringLiteral("add_num"));
        add_num->setMinimum(1);
        add_num->setMaximum(1000000000);

        horizontalLayout_5->addWidget(add_num);

        layoutWidget2 = new QWidget(tab);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(13, 119, 201, 22));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_8 = new QLabel(layoutWidget2);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_4->addWidget(label_8);

        threshold = new QDoubleSpinBox(layoutWidget2);
        threshold->setObjectName(QStringLiteral("threshold"));
        threshold->setDecimals(10);
        threshold->setMinimum(-0.999999);
        threshold->setMaximum(1000);
        threshold->setSingleStep(0.001);

        horizontalLayout_4->addWidget(threshold);

        layoutWidget3 = new QWidget(tab);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(12, 60, 201, 22));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_12 = new QLabel(layoutWidget3);
        label_12->setObjectName(QStringLiteral("label_12"));

        horizontalLayout_3->addWidget(label_12);

        edge_paramete = new QDoubleSpinBox(layoutWidget3);
        edge_paramete->setObjectName(QStringLiteral("edge_paramete"));
        edge_paramete->setDecimals(2);
        edge_paramete->setMinimum(-100);
        edge_paramete->setMaximum(100);
        edge_paramete->setSingleStep(0.1);

        horizontalLayout_3->addWidget(edge_paramete);

        layoutWidget4 = new QWidget(tab);
        layoutWidget4->setObjectName(QStringLiteral("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(13, 3, 201, 22));
        horizontalLayout = new QHBoxLayout(layoutWidget4);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget4);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        radius = new QDoubleSpinBox(layoutWidget4);
        radius->setObjectName(QStringLiteral("radius"));
        radius->setDecimals(5);
        radius->setMinimum(1e-05);
        radius->setMaximum(1000);
        radius->setSingleStep(0.01);
        radius->setValue(1);

        horizontalLayout->addWidget(radius);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        video_speed = new QDoubleSpinBox(tab_2);
        video_speed->setObjectName(QStringLiteral("video_speed"));
        video_speed->setGeometry(QRect(100, 100, 121, 20));
        video_speed->setDecimals(4);
        video_speed->setMaximum(1e+08);
        video_speed->setSingleStep(1);
        video_speed->setValue(1.1);
        label_70 = new QLabel(tab_2);
        label_70->setObjectName(QStringLiteral("label_70"));
        label_70->setGeometry(QRect(41, 100, 91, 20));
        begin_index = new QDoubleSpinBox(tab_2);
        begin_index->setObjectName(QStringLiteral("begin_index"));
        begin_index->setGeometry(QRect(100, 20, 121, 20));
        begin_index->setDecimals(4);
        begin_index->setMaximum(1e+09);
        begin_index->setSingleStep(0.1);
        begin_index->setValue(0);
        pushButton_play_video = new QPushButton(tab_2);
        pushButton_play_video->setObjectName(QStringLiteral("pushButton_play_video"));
        pushButton_play_video->setGeometry(QRect(30, 140, 161, 23));
        label_69 = new QLabel(tab_2);
        label_69->setObjectName(QStringLiteral("label_69"));
        label_69->setGeometry(QRect(20, 60, 122, 20));
        label_64 = new QLabel(tab_2);
        label_64->setObjectName(QStringLiteral("label_64"));
        label_64->setGeometry(QRect(10, 20, 122, 20));
        end_index = new QDoubleSpinBox(tab_2);
        end_index->setObjectName(QStringLiteral("end_index"));
        end_index->setGeometry(QRect(100, 60, 121, 20));
        end_index->setDecimals(4);
        end_index->setMaximum(1e+08);
        end_index->setSingleStep(1);
        end_index->setValue(0);
        label_62 = new QLabel(tab_2);
        label_62->setObjectName(QStringLiteral("label_62"));
        label_62->setGeometry(QRect(2, 200, 122, 20));
        wlop_snapshot_index = new QDoubleSpinBox(tab_2);
        wlop_snapshot_index->setObjectName(QStringLiteral("wlop_snapshot_index"));
        wlop_snapshot_index->setGeometry(QRect(130, 230, 91, 20));
        wlop_snapshot_index->setDecimals(4);
        wlop_snapshot_index->setMaximum(1000);
        wlop_snapshot_index->setSingleStep(1);
        wlop_snapshot_index->setValue(1);
        wlop_snapshot_resolution = new QDoubleSpinBox(tab_2);
        wlop_snapshot_resolution->setObjectName(QStringLiteral("wlop_snapshot_resolution"));
        wlop_snapshot_resolution->setGeometry(QRect(130, 200, 91, 20));
        wlop_snapshot_resolution->setDecimals(4);
        wlop_snapshot_resolution->setMaximum(1000);
        wlop_snapshot_resolution->setSingleStep(0.1);
        wlop_snapshot_resolution->setValue(1);
        label_63 = new QLabel(tab_2);
        label_63->setObjectName(QStringLiteral("label_63"));
        label_63->setGeometry(QRect(2, 230, 122, 20));
        tabWidget->addTab(tab_2, QString());

        retranslateUi(Upsampling_para);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Upsampling_para);
    } // setupUi

    void retranslateUi(QWidget *Upsampling_para)
    {
        Upsampling_para->setWindowTitle(QApplication::translate("Upsampling_para", "Form", 0));
        pushButton_Projection->setText(QApplication::translate("Upsampling_para", "Optimize Projection", 0));
        using_threshol_process->setText(QApplication::translate("Upsampling_para", "Use Stop Threshold:", 0));
        apply_add_point->setText(QApplication::translate("Upsampling_para", "Add Points", 0));
        label_3->setText(QApplication::translate("Upsampling_para", "Psi Sigma:", 0));
        label_7->setText(QApplication::translate("Upsampling_para", "Add Point Num:", 0));
        label_8->setText(QApplication::translate("Upsampling_para", "Threshold:", 0));
        label_12->setText(QApplication::translate("Upsampling_para", "Edge Senstivity:", 0));
        label_2->setText(QApplication::translate("Upsampling_para", "CGrid Radius;", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("Upsampling_para", "Upsample", 0));
        label_70->setText(QApplication::translate("Upsampling_para", "speed", 0));
        pushButton_play_video->setText(QApplication::translate("Upsampling_para", "Play Video", 0));
        label_69->setText(QApplication::translate("Upsampling_para", "end index", 0));
        label_64->setText(QApplication::translate("Upsampling_para", "begin index", 0));
        label_62->setText(QApplication::translate("Upsampling_para", "snapshot resolution", 0));
        label_63->setText(QApplication::translate("Upsampling_para", "snapshot index", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("Upsampling_para", "Video", 0));
    } // retranslateUi

};

namespace Ui {
    class Upsampling_para: public Ui_Upsampling_para {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPSAMPLING_PARA_H

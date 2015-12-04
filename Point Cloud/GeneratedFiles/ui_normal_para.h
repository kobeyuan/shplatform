/********************************************************************************
** Form generated from reading UI file 'normal_para.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NORMAL_PARA_H
#define UI_NORMAL_PARA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_normal_paras
{
public:
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QDoubleSpinBox *radius;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpinBox *KNN;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QDoubleSpinBox *sigma;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QSpinBox *smooth_normal_interate_num;
    QCheckBox *use_anistropic_PCA;
    QPushButton *normal_smoothing;
    QPushButton *normal_PCA;
    QPushButton *pushButton_reorientate_normal;

    void setupUi(QWidget *normal_paras)
    {
        if (normal_paras->objectName().isEmpty())
            normal_paras->setObjectName(QStringLiteral("normal_paras"));
        normal_paras->resize(239, 470);
        normal_paras->setMaximumSize(QSize(189898, 187144));
        groupBox = new QGroupBox(normal_paras);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 231, 171));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        radius = new QDoubleSpinBox(groupBox);
        radius->setObjectName(QStringLiteral("radius"));
        radius->setDecimals(5);
        radius->setMinimum(1e-05);
        radius->setMaximum(1000);
        radius->setSingleStep(0.01);
        radius->setValue(1);

        horizontalLayout->addWidget(radius);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        KNN = new QSpinBox(groupBox);
        KNN->setObjectName(QStringLiteral("KNN"));
        KNN->setMinimum(1);
        KNN->setMaximum(10000);
        KNN->setValue(6);

        horizontalLayout_2->addWidget(KNN);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        sigma = new QDoubleSpinBox(groupBox);
        sigma->setObjectName(QStringLiteral("sigma"));
        sigma->setDecimals(3);
        sigma->setMaximum(180);
        sigma->setValue(20);

        horizontalLayout_3->addWidget(sigma);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_4->addWidget(label_4);

        smooth_normal_interate_num = new QSpinBox(groupBox);
        smooth_normal_interate_num->setObjectName(QStringLiteral("smooth_normal_interate_num"));
        smooth_normal_interate_num->setMinimum(1);
        smooth_normal_interate_num->setMaximum(100);
        smooth_normal_interate_num->setValue(5);

        horizontalLayout_4->addWidget(smooth_normal_interate_num);


        verticalLayout->addLayout(horizontalLayout_4);

        use_anistropic_PCA = new QCheckBox(groupBox);
        use_anistropic_PCA->setObjectName(QStringLiteral("use_anistropic_PCA"));

        verticalLayout->addWidget(use_anistropic_PCA);

        normal_smoothing = new QPushButton(normal_paras);
        normal_smoothing->setObjectName(QStringLiteral("normal_smoothing"));
        normal_smoothing->setGeometry(QRect(30, 240, 171, 31));
        normal_PCA = new QPushButton(normal_paras);
        normal_PCA->setObjectName(QStringLiteral("normal_PCA"));
        normal_PCA->setGeometry(QRect(30, 190, 171, 31));
        pushButton_reorientate_normal = new QPushButton(normal_paras);
        pushButton_reorientate_normal->setObjectName(QStringLiteral("pushButton_reorientate_normal"));
        pushButton_reorientate_normal->setGeometry(QRect(30, 290, 171, 31));

        retranslateUi(normal_paras);

        QMetaObject::connectSlotsByName(normal_paras);
    } // setupUi

    void retranslateUi(QWidget *normal_paras)
    {
        normal_paras->setWindowTitle(QApplication::translate("normal_paras", "normal paras", 0));
        groupBox->setTitle(QString());
        label->setText(QApplication::translate("normal_paras", "Smoothing Radius", 0));
        label_2->setText(QApplication::translate("normal_paras", "PCA KNN", 0));
        label_3->setText(QApplication::translate("normal_paras", "Sigma", 0));
        label_4->setText(QApplication::translate("normal_paras", "Iterate Num", 0));
        use_anistropic_PCA->setText(QApplication::translate("normal_paras", " Use Anistropic PCA", 0));
        normal_smoothing->setText(QApplication::translate("normal_paras", "Normal Smoothing", 0));
        normal_PCA->setText(QApplication::translate("normal_paras", "PCA Normal", 0));
        pushButton_reorientate_normal->setText(QApplication::translate("normal_paras", "Reorientate Normal", 0));
    } // retranslateUi

};

namespace Ui {
    class normal_paras: public Ui_normal_paras {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NORMAL_PARA_H

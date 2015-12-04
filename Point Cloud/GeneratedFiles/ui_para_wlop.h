/********************************************************************************
** Form generated from reading UI file 'para_wlop.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARA_WLOP_H
#define UI_PARA_WLOP_H

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
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_para_wlop
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QDoubleSpinBox *radius;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QDoubleSpinBox *mu;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpinBox *iter;
    QLabel *label_3;
    QCheckBox *compute_density;
    QCheckBox *compute_pca;
    QPushButton *anisotropic_lop_apply;
    QPushButton *wlop_apply;

    void setupUi(QWidget *para_wlop)
    {
        if (para_wlop->objectName().isEmpty())
            para_wlop->setObjectName(QStringLiteral("para_wlop"));
        para_wlop->resize(293, 458);
        layoutWidget = new QWidget(para_wlop);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 271, 191));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        radius = new QDoubleSpinBox(layoutWidget);
        radius->setObjectName(QStringLiteral("radius"));
        radius->setDecimals(5);
        radius->setMinimum(1e-05);
        radius->setMaximum(1000);
        radius->setSingleStep(0.01);
        radius->setValue(1);

        horizontalLayout->addWidget(radius);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_3->addWidget(label_4);

        mu = new QDoubleSpinBox(layoutWidget);
        mu->setObjectName(QStringLiteral("mu"));
        mu->setDecimals(5);
        mu->setSingleStep(0.1);

        horizontalLayout_3->addWidget(mu);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        iter = new QSpinBox(layoutWidget);
        iter->setObjectName(QStringLiteral("iter"));
        iter->setMaximum(1000);
        iter->setValue(1);

        horizontalLayout_2->addWidget(iter);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_2->addWidget(label_3);


        verticalLayout->addLayout(horizontalLayout_2);

        compute_density = new QCheckBox(layoutWidget);
        compute_density->setObjectName(QStringLiteral("compute_density"));

        verticalLayout->addWidget(compute_density);

        compute_pca = new QCheckBox(layoutWidget);
        compute_pca->setObjectName(QStringLiteral("compute_pca"));

        verticalLayout->addWidget(compute_pca);

        anisotropic_lop_apply = new QPushButton(para_wlop);
        anisotropic_lop_apply->setObjectName(QStringLiteral("anisotropic_lop_apply"));
        anisotropic_lop_apply->setGeometry(QRect(50, 300, 161, 31));
        wlop_apply = new QPushButton(para_wlop);
        wlop_apply->setObjectName(QStringLiteral("wlop_apply"));
        wlop_apply->setGeometry(QRect(30, 240, 209, 31));

        retranslateUi(para_wlop);

        QMetaObject::connectSlotsByName(para_wlop);
    } // setupUi

    void retranslateUi(QWidget *para_wlop)
    {
        para_wlop->setWindowTitle(QApplication::translate("para_wlop", "WLOP parameters setting", 0));
        label->setText(QApplication::translate("para_wlop", "Radius:", 0));
        label_4->setText(QApplication::translate("para_wlop", "Mu", 0));
        label_2->setText(QApplication::translate("para_wlop", "Iterate ", 0));
        label_3->setText(QApplication::translate("para_wlop", "times", 0));
        compute_density->setText(QApplication::translate("para_wlop", "Compute Density", 0));
        compute_pca->setText(QApplication::translate("para_wlop", "Compute PCA Normal Each Iteration", 0));
        anisotropic_lop_apply->setText(QApplication::translate("para_wlop", "Anisotropic LOP(for EAR)", 0));
        wlop_apply->setText(QApplication::translate("para_wlop", "WLOP", 0));
    } // retranslateUi

};

namespace Ui {
    class para_wlop: public Ui_para_wlop {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARA_WLOP_H

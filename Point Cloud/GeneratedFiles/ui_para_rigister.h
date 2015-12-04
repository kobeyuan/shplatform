/********************************************************************************
** Form generated from reading UI file 'para_rigister.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARA_RIGISTER_H
#define UI_PARA_RIGISTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_rigister
{
public:
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QSpinBox *tdouble;
    QWidget *formLayoutWidget_2;
    QFormLayout *formLayout_2;
    QLabel *label_2;
    QDoubleSpinBox *doubleSpinBox;
    QPushButton *SparseICP;

    void setupUi(QWidget *rigister)
    {
        if (rigister->objectName().isEmpty())
            rigister->setObjectName(QStringLiteral("rigister"));
        rigister->resize(222, 446);
        rigister->setMaximumSize(QSize(155555, 15555));
        formLayoutWidget = new QWidget(rigister);
        formLayoutWidget->setObjectName(QStringLiteral("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(9, 9, 181, 91));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(formLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        tdouble = new QSpinBox(formLayoutWidget);
        tdouble->setObjectName(QStringLiteral("tdouble"));

        formLayout->setWidget(0, QFormLayout::FieldRole, tdouble);

        formLayoutWidget_2 = new QWidget(rigister);
        formLayoutWidget_2->setObjectName(QStringLiteral("formLayoutWidget_2"));
        formLayoutWidget_2->setGeometry(QRect(9, 212, 191, 51));
        formLayout_2 = new QFormLayout(formLayoutWidget_2);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(formLayoutWidget_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_2);

        doubleSpinBox = new QDoubleSpinBox(formLayoutWidget_2);
        doubleSpinBox->setObjectName(QStringLiteral("doubleSpinBox"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, doubleSpinBox);

        SparseICP = new QPushButton(rigister);
        SparseICP->setObjectName(QStringLiteral("SparseICP"));
        SparseICP->setGeometry(QRect(60, 300, 75, 23));

        retranslateUi(rigister);

        QMetaObject::connectSlotsByName(rigister);
    } // setupUi

    void retranslateUi(QWidget *rigister)
    {
        rigister->setWindowTitle(QApplication::translate("rigister", "Form", 0));
        label->setText(QApplication::translate("rigister", "TestUI", 0));
        label_2->setText(QApplication::translate("rigister", "Tinput", 0));
        SparseICP->setText(QApplication::translate("rigister", "SparseICP", 0));
    } // retranslateUi

};

namespace Ui {
    class rigister: public Ui_rigister {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARA_RIGISTER_H

/********************************************************************************
** Form generated from reading UI file 'bloodnewwindows.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BLOODNEWWINDOWS_H
#define UI_BLOODNEWWINDOWS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "qchartview.h"

QT_BEGIN_NAMESPACE

class Ui_BloodNewWindows
{
public:
    QtCharts::QChartView *graphicsView_1;
    QPushButton *btnClear;
    QPushButton *btnStartAndStop;
    QLabel *label;

    void setupUi(QWidget *BloodNewWindows)
    {
        if (BloodNewWindows->objectName().isEmpty())
            BloodNewWindows->setObjectName(QString::fromUtf8("BloodNewWindows"));
        BloodNewWindows->resize(480, 387);
        graphicsView_1 = new QtCharts::QChartView(BloodNewWindows);
        graphicsView_1->setObjectName(QString::fromUtf8("graphicsView_1"));
        graphicsView_1->setGeometry(QRect(0, 50, 471, 331));
        graphicsView_1->setFocusPolicy(Qt::ClickFocus);
        btnClear = new QPushButton(BloodNewWindows);
        btnClear->setObjectName(QString::fromUtf8("btnClear"));
        btnClear->setGeometry(QRect(290, 10, 80, 31));
        btnStartAndStop = new QPushButton(BloodNewWindows);
        btnStartAndStop->setObjectName(QString::fromUtf8("btnStartAndStop"));
        btnStartAndStop->setGeometry(QRect(380, 10, 83, 31));
        label = new QLabel(BloodNewWindows);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 20, 79, 19));

        retranslateUi(BloodNewWindows);

        QMetaObject::connectSlotsByName(BloodNewWindows);
    } // setupUi

    void retranslateUi(QWidget *BloodNewWindows)
    {
        BloodNewWindows->setWindowTitle(QApplication::translate("BloodNewWindows", "Form", nullptr));
        btnClear->setText(QApplication::translate("BloodNewWindows", "\346\270\205\351\231\244\346\233\262\347\272\277", nullptr));
        btnStartAndStop->setText(QApplication::translate("BloodNewWindows", "\345\220\257\345\212\250\345\256\232\346\227\266\345\231\250", nullptr));
        label->setText(QApplication::translate("BloodNewWindows", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BloodNewWindows: public Ui_BloodNewWindows {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BLOODNEWWINDOWS_H

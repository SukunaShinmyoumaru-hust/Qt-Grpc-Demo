/********************************************************************************
** Form generated from reading UI file 'velocitynewwindows.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VELOCITYNEWWINDOWS_H
#define UI_VELOCITYNEWWINDOWS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "qchartview.h"

QT_BEGIN_NAMESPACE

class Ui_velocityNewWindows
{
public:
    QLabel *label;
    QPushButton *btnStartAndStop;
    QPushButton *btnClear;
    QtCharts::QChartView *graphicsView_1;

    void setupUi(QWidget *velocityNewWindows)
    {
        if (velocityNewWindows->objectName().isEmpty())
            velocityNewWindows->setObjectName(QString::fromUtf8("velocityNewWindows"));
        velocityNewWindows->resize(499, 429);
        label = new QLabel(velocityNewWindows);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 20, 79, 19));
        btnStartAndStop = new QPushButton(velocityNewWindows);
        btnStartAndStop->setObjectName(QString::fromUtf8("btnStartAndStop"));
        btnStartAndStop->setGeometry(QRect(390, 10, 83, 31));
        btnClear = new QPushButton(velocityNewWindows);
        btnClear->setObjectName(QString::fromUtf8("btnClear"));
        btnClear->setGeometry(QRect(300, 10, 80, 31));
        graphicsView_1 = new QtCharts::QChartView(velocityNewWindows);
        graphicsView_1->setObjectName(QString::fromUtf8("graphicsView_1"));
        graphicsView_1->setGeometry(QRect(10, 50, 471, 331));
        graphicsView_1->setFocusPolicy(Qt::ClickFocus);

        retranslateUi(velocityNewWindows);

        QMetaObject::connectSlotsByName(velocityNewWindows);
    } // setupUi

    void retranslateUi(QWidget *velocityNewWindows)
    {
        velocityNewWindows->setWindowTitle(QApplication::translate("velocityNewWindows", "Form", nullptr));
        label->setText(QApplication::translate("velocityNewWindows", "TextLabel", nullptr));
        btnStartAndStop->setText(QApplication::translate("velocityNewWindows", "\345\220\257\345\212\250\345\256\232\346\227\266\345\231\250", nullptr));
        btnClear->setText(QApplication::translate("velocityNewWindows", "\346\270\205\351\231\244\346\233\262\347\272\277", nullptr));
    } // retranslateUi

};

namespace Ui {
    class velocityNewWindows: public Ui_velocityNewWindows {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VELOCITYNEWWINDOWS_H

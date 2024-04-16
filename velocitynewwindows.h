#ifndef VELOCITYNEWWINDOWS_H
#define VELOCITYNEWWINDOWS_H

#include <QWidget>
#include "chart.h"

namespace Ui {
class velocityNewWindows;
}

class velocityNewWindows : public QWidget{
        Q_OBJECT
public:
        explicit velocityNewWindows(int a,QWidget *parent = nullptr);
        ~velocityNewWindows();

        /* 用于模拟生成实时数据的定时器 */
        QTimer* m_timer;

        /* 用来记录数据点数 */
        int pointCount = 0;

        /* to determine which robot */
        int robot;
        double v;
private:
        Ui::velocityNewWindows *ui;
        Chart velocity;
private slots:
        void slotBtnClear();
        void slotBtnStartAndStop();
        void slotTimeout();
    };

#endif // VELOCITYNEWWINDOWS_H

#ifndef BLOODNEWWINDOWS_H
#define BLOODNEWWINDOWS_H

#include <QWidget>
#include "chart.h"

namespace Ui {
class BloodNewWindows;
}

class BloodNewWindows : public QWidget
{
    Q_OBJECT

public:
    explicit BloodNewWindows(int a,QWidget *parent = nullptr);
    ~BloodNewWindows();

    /* 用于模拟生成实时数据的定时器 */
    QTimer* m_timer;

    /* 用来记录数据点数 */
    int pointCount = 0;

    /* to determine which robot */
    int robot;
    int b;
private:
    Ui::BloodNewWindows *ui;
    Chart blood;

private slots:
    void slotBtnClear();
    void slotBtnStartAndStop();
    void slotTimeout();
};

#endif // BLOODNEWWINDOWS_H

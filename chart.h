#ifndef CHART_H
#define CHART_H


#include <QTimer>
#include <QChartView>
#include <QValueAxis>
#include <QLineSeries>
#include <QMessageBox>

/* 横纵坐标最大显示范围 */
const int AXIS_MAX_Y = 10;
const int MAX_VELOCITY = 3;
const int MAX_BLOOD = 1000;

/* 光添加头文件QChartView还不够，还需要引入QChart的命名空间 */
QT_CHARTS_USE_NAMESPACE

class Chart{
public:
    /* 图表对象 */
    QChart* m_chart;

    /* 横纵坐标轴对象 */
    QValueAxis *m_axisX, *m_axisY;

    /* 曲线图对象 */
    QLineSeries* m_lineSeries;

    Chart(const char* x_string,const char* y_string,const char* title_string,int max_y);
    ~Chart();

    void Update(QPointF f);
    void Erase(int pointCount);
    void Empty();

};


#endif // CHART_H

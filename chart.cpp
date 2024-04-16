#include "chart.h"

Chart::Chart(const char* x_string,const char* y_string,const char* title_string,int max_x){
    m_axisX = new QValueAxis();
    m_axisY = new QValueAxis();
    m_axisX->setTitleText(x_string);
    m_axisY->setTitleText(y_string);
    m_axisX->setMin(0);
    m_axisY->setMin(0);
    m_axisX->setMax(max_x);
    m_axisY->setMax(AXIS_MAX_Y);

    m_lineSeries = new QLineSeries();                             // 创建曲线绘制对象
    m_lineSeries->setPointsVisible(true);                         // 设置数据点可见
    m_lineSeries->setName(title_string);                          // 图例名称

    m_chart = new QChart();                                        // 创建图表对象
    m_chart->addAxis(m_axisX, Qt::AlignLeft);                      // 将X轴添加到图表上
    m_chart->addAxis(m_axisY, Qt::AlignBottom);                    // 将Y轴添加到图表上
    m_chart->addSeries(m_lineSeries);                              // 将曲线对象添加到图表上
    m_chart->setAnimationOptions(QChart::SeriesAnimations);        // 动画：能使曲线绘制显示的更平滑，过渡效果更好看

    m_lineSeries->attachAxis(m_axisX);                             // 曲线对象关联上X轴，此步骤必须在m_chart->addSeries之后
    m_lineSeries->attachAxis(m_axisY);                             // 曲线对象关联上Y轴，此步骤必须在m_chart->addSeries之后
}
Chart::~Chart(){

}
void Chart::Update(QPointF f){
    m_lineSeries->append(f);
}
void Chart::Erase(int pointCount){
    m_lineSeries->remove(0);
    m_chart->axisX()->setMin(pointCount - AXIS_MAX_Y);
    m_chart->axisX()->setMax(pointCount);                    // 更新X轴范围
}
void Chart::Empty(){
    m_lineSeries->clear();
    m_chart->axisX()->setMin(0);
    m_chart->axisX()->setMax(AXIS_MAX_Y);
}

#include "velocitynewwindows.h"
#include "ui_velocitynewwindows.h"

velocityNewWindows::velocityNewWindows(int a,QWidget *parent) :
    robot(a),
    QWidget(parent),
    ui(new Ui::velocityNewWindows),
    velocity("速度","时间","小车速度",MAX_VELOCITY)
{
    ui->setupUi(this);

    m_timer = new QTimer(this);
    m_timer->setSingleShot(false);
    QObject::connect(m_timer, SIGNAL(timeout()), this, SLOT(slotTimeout()));
    QObject::connect(ui->btnClear, SIGNAL(clicked(bool)), this, SLOT(slotBtnClear()));
    QObject::connect(ui->btnStartAndStop, SIGNAL(clicked(bool)), this, SLOT(slotBtnStartAndStop()));
    QString name;

    ui->graphicsView_1->setChart(velocity.m_chart);                           // 将图表对象设置到graphicsView上进行显示
    ui->graphicsView_1->setRenderHint(QPainter::Antialiasing);       // 设置渲染：抗锯齿，如果不设置那么曲线就显得不平滑

    switch(robot){
        case 0: name = QString("Red1");  break;
        case 1: name = QString("Red2");  break;
        case 2: name = QString("Blue1"); break;
        case 3: name = QString("Blue2"); break;
    }

    ui->label->setText(name);
}

velocityNewWindows::~velocityNewWindows()
{
    delete ui;
}

void velocityNewWindows::slotBtnStartAndStop()
{
    if(m_timer->isActive())
    {
        m_timer->stop();
        ui->btnStartAndStop->setText("启动定时器");
    }else
    {
        pointCount = 0;
        m_timer->start(200);
        ui->btnStartAndStop->setText("停止定时器");
    }
}


void velocityNewWindows::slotTimeout()
{
    if(pointCount > AXIS_MAX_Y)
    {
        velocity.Erase(pointCount);
    }
    velocity.Update(QPointF(pointCount, rand()%100));
    pointCount++;
}

void velocityNewWindows::slotBtnClear()
{
    velocity.Empty();
    pointCount = 0;
}

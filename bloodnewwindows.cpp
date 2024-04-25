#include "bloodnewwindows.h"
#include "ui_bloodnewwindows.h"

BloodNewWindows::BloodNewWindows(int a,QWidget *parent) :
    robot(a),
    QWidget(parent),
    ui(new Ui::BloodNewWindows),
    blood("血量","时间","小车血量",MAX_BLOOD)
{
    ui->setupUi(this);
    b = 0;
    m_timer = new QTimer(this);
    m_timer->setSingleShot(false);
    QObject::connect(m_timer, SIGNAL(timeout()), this, SLOT(slotTimeout()));
    QObject::connect(ui->btnClear, SIGNAL(clicked(bool)), this, SLOT(slotBtnClear()));
    QObject::connect(ui->btnStartAndStop, SIGNAL(clicked(bool)), this, SLOT(slotBtnStartAndStop()));
    QString name;

    ui->graphicsView_1->setChart(blood.m_chart);                           // 将图表对象设置到graphicsView上进行显示
    ui->graphicsView_1->setRenderHint(QPainter::Antialiasing);       // 设置渲染：抗锯齿，如果不设置那么曲线就显得不平滑

    switch(robot){
        case 0: name = QString("Red1");  break;
        case 1: name = QString("Red2");  break;
        case 2: name = QString("Blue1"); break;
        case 3: name = QString("Blue2"); break;
    }

    ui->label->setText(name);
}

BloodNewWindows::~BloodNewWindows()
{
    delete ui;
}

void BloodNewWindows::slotBtnStartAndStop()
{
    if(m_timer->isActive())
    {
        m_timer->stop();
        ui->btnStartAndStop->setText("启动定时器");
    }else
    {
        pointCount = 0;
        m_timer->start(1000);
        ui->btnStartAndStop->setText("停止定时器");
    }
}


void BloodNewWindows::slotTimeout()
{
    if(pointCount > AXIS_MAX_Y)
    {
        blood.Erase(pointCount);
    }
    blood.Update(QPointF(pointCount, b));
    pointCount++;
}

void BloodNewWindows::slotBtnClear()
{
    blood.Empty();
    pointCount = 0;
}

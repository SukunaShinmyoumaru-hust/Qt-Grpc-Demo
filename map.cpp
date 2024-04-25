#include "map.h"
#include "ui_map.h"
#include <iostream>

Map::Map(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Map)
{
    ui->setupUi(this);
    QObject::connect(ui->testButton_4, SIGNAL(clicked(bool)), this, SLOT(testmap()));
    // setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    // hide();
}

Map::~Map()
{
    delete ui;
}

void Map::updatePosition(int id,double x1,double y1){
    x[id * 2 + 1] = x1 / 8.08 * this->height();
    x[id * 2 + 0] = y1 / 4.48 * this->width();
    // printf("Draw a point at %d %d\n",x[id*2+0],x[id*2+1]);
    this->update();
}

void Map::testmap(){

    for(int i = 0;i < 8;i++){
        x[i] = 150 + 6 * (i - 4);
    }
    this->update();
}

void Map::paintEvent(QPaintEvent *){
    QPainter* painter = new QPainter(this);
    // painter->begin(this);
    painter->setRenderHint(QPainter::Antialiasing, true);
    // painter->drawPixmap(rect(),QPixmap("./map.png"));
    // 使用相对路径出错了!
    QImage image("../map.png");
    if (image.isNull()) {
        std::cout << "无法加载图片";
        return;
    }
    painter->drawImage(0, 0, image);
    QPointF pointf[2] = { QPoint(0,0),QPoint(0,0)};
    painter->setPen(QPen(Qt::red,10,Qt::SolidLine,Qt::RoundCap));
    for (int i=0; i<2; i++){
       pointf[i].setX(x[i * 2 + 0]);
       pointf[i].setY(x[i * 2 + 1]);
    }
    painter->drawPoints(pointf, 2);

    painter->setPen(QPen(Qt::blue,10,Qt::SolidLine,Qt::RoundCap));
    for (int i=2; i<4; i++){
       pointf[i-2].setX(x[i * 2 + 0]);
       pointf[i-2].setY(x[i * 2 + 1]);
    }
    painter->drawPoints(pointf, 2);
    painter->end();
}

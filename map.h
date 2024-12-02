#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QLabel>
#include <QTableView>
#include <QMessageBox>
#include <QSignalMapper>
#include <QTextBrowser>
#include <QFrame>
#include <QPropertyAnimation>
#include <QStandardItemModel>
#include <QMouseEvent>
#include <QImage>
#include <grpc++/grpc++.h>
#include "proto/communication.grpc.pb.h"
#include "proto/communication.pb.h"

namespace Ui {
class Map;
}

class Map : public QWidget
{
    Q_OBJECT

public:
    explicit Map(QWidget *parent = nullptr);
    ~Map();
    void updatePosition(int id,double x,double y);
    void get(int*,double*,double*);
protected:

private:
    Ui::Map *ui;
    double x[8] = {0,0,0,0,0,0,0,0};
    double f1;
    double f2;
    int w;
    std::unique_ptr<communication::RobotComm::Stub>* stub_;
private slots:
    void testmap();
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
};

#endif // MAP_H

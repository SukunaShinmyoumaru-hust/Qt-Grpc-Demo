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
#include <QImage>

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

private:
    Ui::Map *ui;
    double x[8] = {0,0,0,0,0,0,0,0};
private slots:
    void testmap();
    void paintEvent(QPaintEvent *);

};

#endif // MAP_H

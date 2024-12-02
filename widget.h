#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QChartView>
#include <QTableView>
#include <QValueAxis>
#include <QLineSeries>
#include <QMessageBox>
#include <QtMath>
#include <QSignalMapper>
#include <QTextBrowser>
#include <QComboBox>
#include <QDial>
#include <QFrame>
#include <QPropertyAnimation>
#include <QStandardItemModel>
#include <iostream>
#include <fstream>
#include <string>
#include <grpc++/grpc++.h>

#include "chart.h"
#include "map.h"
#include "proto/communication.grpc.pb.h"
#include "proto/communication.pb.h"
#include "bloodnewwindows.h"
#include "velocitynewwindows.h"
#include "map.h"
#include <stdio.h>
#include <time.h>
#include <thread>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;


private:
    QTableView* RFID_list[4];
    QFrame* attack_list[16];
    QLabel* attackCount_list[16];
    QTextBrowser* radar_list[4];
    BloodNewWindows* b_list[4];
    velocityNewWindows* v_list[4];
    QPushButton* button[4];
    QLabel* states[4];
    QComboBox* com[4];
    int count[16];
    int bul[4];
    int wheel[4];
    int shoot[4];
    int move[4];
    int start[4];
    double rfid_data[4][20];
    std::mutex myMutex;
    QTimer* m_timer;
    QSignalMapper* buttonMapper;
    QPropertyAnimation ani;
    Map* m;
    QDial dial;
    std::unique_ptr<communication::RobotComm::Stub> stub_[4];
    grpc::Status status;
    /* Get */
    communication::Blood b_[4];
    communication::CommonRequest r_;
    communication::Bullet a_[4];
    communication::Posture p_[4];
    communication::GimbalYaw g_[4];
    communication::Velocity v_[4];
    communication::Attacked aff_[4];
    communication::ObjectDection obj_[4];
    /* Post */
    communication::Blood b_set_[4];
    communication::Bullet a_set_[4];
    communication::Destination d_set_[4];
    communication::FricWheel f_set_[4];
    communication::ChassisStop s_set_[4];
    communication::Shooter bu_set_[4];
private:
    void hitAction(int hit,int t);
    void rfidInterface(int id,int l);
    void setButtonMap();
    void setShowMap();
    double getData(int command);
    void showInformation(int a);
    void showBulletInformation(int a);
    void sentInformation(int a);
    void sentBloodInformation(int a);
    void showBlood(int a);
    void showVelocity(int a);
    void radarInterface(int id,int x,int y);
    void mapInterface();
    void sendBulletMessage(int id,int way);
    void setwheelStatus(int id);
    void setshootStatus(int id);
    void setmoveStatus(int id);
    void getBlood();
    void getBullet();
    void getPosture();
    void getGunposture();
    void getVelocity();
    void getAffected();
    void getObjectDection();
    void allControl(int id);
    void threadFunction();

private slots:
    void slotTimeout();
    void handleButton(int b);
    void eraseHit();
    void eraseRFID();
    void eraseradar();
    void testHit();
    void testRFID();
    void testradar();
    void pushcommand();
};

#endif // WIDGET_H

#include "widget.h"
#include "ui_widget.h"


#define MAP_X 1319
#define MAP_Y 70

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->state->setText("初始化");

    m_timer = new QTimer(this);
    m_timer->setSingleShot(false);

    buttonMapper = new QSignalMapper;
    ui->state->setText("按钮初始化");
    setButtonMap();
    setShowMap();
    QObject::connect(buttonMapper, SIGNAL(mapped(int)), this, SLOT(handleButton(int)));
    QObject::connect(ui->testButton, SIGNAL(clicked(bool)), this, SLOT(testHit()));
    QObject::connect(ui->testButton_2, SIGNAL(clicked(bool)), this, SLOT(testRFID()));
    QObject::connect(ui->testButton_3, SIGNAL(clicked(bool)), this, SLOT(testradar()));

    QObject::connect(ui->eraseButton, SIGNAL(clicked(bool)), this, SLOT(eraseHit()));
    QObject::connect(ui->eraseButton_2, SIGNAL(clicked(bool)), this, SLOT(eraseRFID()));
    QObject::connect(ui->eraseButton_3, SIGNAL(clicked(bool)), this, SLOT(eraseradar()));
    QObject::connect(m_timer, SIGNAL(timeout()), this, SLOT(slotTimeout()));
    ui->state->setText("地图初始化");
    m = new Map();
    ui->horizontalLayout->addWidget(m);

    ui->state->setText("连接机器人中");
    std::ifstream file("../ip.txt");
    std::string line;

    if (file.is_open()) {
        for(int i = 0;i < 4;i++){
            std::getline(file, line);
            std::cout << "Initial " << i << " " << line << std::endl;

            std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel(line, grpc::InsecureChannelCredentials());
            stub_[i] = communication::RobotComm::NewStub(channel);

            if(!stub_[i]) std::cout << "Network connection failed" << std::endl;
        }
        file.close();
    } else {
        std::cout << "无法打开文件" << std::endl;
    }
    ui->state->setText("等待命令");
    m_timer->start(1000);
}

Widget::~Widget()
{
    delete ui;
}


/*
 * showInformation
 * This function show the detail information of robot
 * a: the id of robot
 */
void Widget::showInformation(int a){
    QString name;
    switch(a){
        case 0: name = QString("Red1");  break;
        case 1: name = QString("Red2");  break;
        case 2: name = QString("Blue1"); break;
        case 3: name = QString("Blue2"); break;
    }

    QMessageBox::about(NULL, name, "Message Box");
}

/*
 * showBulletInformation
 * This function show the detail information of robot
 * a: the id of robot
 */
void Widget::showBulletInformation(int a){
    QString name;
    switch(a){
        case 0: name = QString("Red1");  break;
        case 1: name = QString("Red2");  break;
        case 2: name = QString("Blue1"); break;
        case 3: name = QString("Blue2"); break;
    }
    QString info = "bullet number is " + QString::number(bul[a]);
    QMessageBox::about(NULL, name, info);
}

/*
 * sentInformation
 * This function send the information of navigation command
 * a: the id of robot
 */
void Widget::sentInformation(int a){
    QString name;
    grpc::ClientContext context;
    double x,y;
    switch(a){
        case 0: name = QString("Red1");  break;
        case 1: name = QString("Red2");  break;
        case 2: name = QString("Blue1"); break;
        case 3: name = QString("Blue2"); break;
    }
    switch(a){
        case 0:
            x = ui->xSpinBox_red_1->value();
            y = ui->ySpinBox_red_1->value();
            break;
        case 1:
            x = ui->xSpinBox_red_2->value();
            y = ui->ySpinBox_red_2->value();
            break;
        case 2:
            x = ui->xSpinBox_blue_1->value();
            y = ui->ySpinBox_blue_1->value();
            break;
        case 3:
            x = ui->xSpinBox_blue_2->value();
            y = ui->ySpinBox_blue_2->value();
            break;
    }
    d_set_[a].set_x(x);
    d_set_[a].set_y(y);
    communication::Response re;
    grpc::Status s_ = stub_[a]->PostDestination(&context,d_set_[a],&re);
    QString info;
    if(s_.ok()) info = QString("Get the information: x is ") + QString::number(x,'f',2) + QString(" y is ") + QString::number(y,'f',2);
    else info = QString("There's sth Wrong");
    QMessageBox::information(this,name,info);
}

/*
 * sendBloodInformation
 * This function send the command of blood
 * a: the id of robot
 */
void Widget::sentBloodInformation(int a){
    QString name;
    grpc::ClientContext context;
    int blood;
    switch(a){
        case 0: name = QString("Red1");  break;
        case 1: name = QString("Red2");  break;
        case 2: name = QString("Blue1"); break;
        case 3: name = QString("Blue2"); break;
    }
    switch(a){
        case 0:
            blood = ui->spinBox_red_1->value();
            break;
        case 1:
            blood = ui->spinBox_red_2->value();
            break;
        case 2:
            blood = ui->spinBox_blue_1->value();
            break;
        case 3:
            blood = ui->spinBox_blue_2->value();
            break;
    }
    b_set_[a].set_blood(blood);
    communication::Response re;
    grpc::Status s_ = stub_[a]->PostBlood(&context,b_set_[a],&re);
    QString info;
    if(s_.ok()) info = QString("Get the information") + QString::number(blood);
    else info = QString("There's sth Wrong");
    QMessageBox::information(this,name,info);
}


/*
 * showBlood
 * when click a button, this function is called. Open a new widget and show the information of blood
 * b: the id of robot
 */
void Widget::showBlood(int b){
    b_list[b]->show();
}

/*
 * showVelocity
 * when click a button, this function is called. Open a new widget and show the information of velocity
 * b: the id of robot
 */
void Widget::showVelocity(int b){
    v_list[b]->show();
}

/*
 * slot: handleButton
 * the button has a tag, based on the tag of button to handle the event.
 * r: the tag of button
 */
void Widget::handleButton(int r){
    int s = r / 4;
    int k = r % 4;
    switch(s){
        case 0: showBlood(k);                  break;
        case 1: showVelocity(k);               break;
        case 2: showInformation(k);            break;
        case 3: showBulletInformation(k);      break;
        case 4: sentInformation(k);            break;
        case 5: sentBloodInformation(k);       break;
        case 6: sendBulletMessage(k,1);        break;
        case 7: setwheelStatus(k);             break;
        case 8: setshootStatus(k);             break;
        case 9: setmoveStatus(k);              break;
        case 10: sendBulletMessage(k,2);       break;
        case 11: allControl(k);                break;
    }
}

void Widget::allControl(int id){
    ui->state->setText("发送控制信息");
    QString name;
    grpc::ClientContext context;
    switch(id){
        case 0: name = QString("Red1");  break;
        case 1: name = QString("Red2");  break;
        case 2: name = QString("Blue1"); break;
        case 3: name = QString("Blue2"); break;
    }
    communication::CommonRequest a;
    a.set_time(0);
    QString info;
    communication::Response re;
    grpc::Status s_ = stub_[id]->PostSystemRun(&context,a,&re);
    if(s_.ok()){
        if(start[id] == 0){
            button[id]->setText("总控关闭");
        }
        else{
            button[id]->setText("总控开启");
        }
        info = QString("OK");
        start[id] = start[id] ^ 1;
    }
    else{
        info = QString("There's sth Wrong");
    }
    QMessageBox::information(this,name,info);
    ui->state->setText("等待命令");
}

void Widget::sendBulletMessage(int id,int way){
    QString name;
    grpc::ClientContext context;
    int bl;
    switch(id){
        case 0: name = QString("Red1");  break;
        case 1: name = QString("Red2");  break;
        case 2: name = QString("Blue1"); break;
        case 3: name = QString("Blue2"); break;
    }
    switch(id){
        case 0:
            bl = ui->bulletBox_red_1->value();
            break;
        case 1:
            bl = ui->bulletBox_red_2->value();
            break;
        case 2:
            bl = ui->bulletBox_blue_1->value();
            break;
        case 3:
            bl = ui->bulletBox_blue_2->value();
            break;
    }
    a_set_[id].set_bullets(bl);
    a_set_[id].set_type(way);
    QString info;
    communication::Response re;
    grpc::Status s_ = stub_[id]->PostBullet(&context,a_set_[id],&re);
    if(s_.ok()) info = QString("Get the information ") + QString::number(bl);
    else info = QString("There's sth Wrong");
    QMessageBox::information(this,name,info);
}

void Widget::setwheelStatus(int id){
    QString name;
    grpc::ClientContext context;
    switch(id){
        case 0: name = QString("Red1");  break;
        case 1: name = QString("Red2");  break;
        case 2: name = QString("Blue1"); break;
        case 3: name = QString("Blue2"); break;
    }
    wheel[id] = wheel[id] ^ 1;
    f_set_[id].set_open(wheel[id]);
    QString info;
    communication::Response re;
    grpc::Status s_ = stub_[id]->PostFricWheel(&context,f_set_[id],&re);
    if(s_.ok()) info = QString("Get the information ");
    else info = QString("There's sth Wrong");
    QMessageBox::information(this,name,info);
}

void Widget::setshootStatus(int id){
    QString name;
    grpc::ClientContext context;
    switch(id){
        case 0: name = QString("Red1");  break;
        case 1: name = QString("Red2");  break;
        case 2: name = QString("Blue1"); break;
        case 3: name = QString("Blue2"); break;
    }
    shoot[id] = shoot[id] ^ 1;
    bu_set_[id].set_open(shoot[id]);
    QString info;
    communication::Response re;
    grpc::Status s_ = stub_[id]->PostShooter(&context,bu_set_[id],&re);
    if(s_.ok()) info = QString("Get the information ");
    else info = QString("There's sth Wrong");
    QMessageBox::information(this,name,info);
}

void Widget::setmoveStatus(int id){
    QString name;
    grpc::ClientContext context;
    switch(id){
        case 0: name = QString("Red1");  break;
        case 1: name = QString("Red2");  break;
        case 2: name = QString("Blue1"); break;
        case 3: name = QString("Blue2"); break;
    }
    move[id] = move[id] ^ 1;
    s_set_[id].set_flag(move[id]);
    QString info;
    communication::Response re;
    grpc::Status s_ = stub_[id]->PostChassisStop(&context,s_set_[id],&re);
    if(s_.ok()) info = QString("Get the information ");
    else info = QString("There's sth Wrong");
    QMessageBox::information(this,name,info);
}

/*
 * hitAction
 * a interface of hit model, when the robot hits, call this function
 * id: which robot and where is hit.
 */
void Widget::hitAction(int id,int t){
    count[id]+=t;
    attackCount_list[id]->setText(QString::number(count[id]));
}

/*
 * rfidInterface
 * a interface of rfid model, show the rfid information
 * Not safe!!!!!! Now is safe....
 * id: the id of robot
 * l: the number of tags
 * Please obey the following rules:
 * | 1st x | 1st y | 2nd x | 2nd y |...
 */
void Widget::rfidInterface(int id,int l){
    QStandardItemModel* model = new QStandardItemModel(l,2);
    model->setHorizontalHeaderLabels({"x", "y"});

    for(int i = 0;i < l;i++){
        model->setItem(i, 0, new QStandardItem(QString::number(rfid_data[id][2 * i + 0])));
        model->setItem(i, 1, new QStandardItem(QString::number(rfid_data[id][2 * i + 1])));
    }
    RFID_list[id]->setModel(model);
    RFID_list[id]->show();
    // free(r);
}

void Widget::radarInterface(int id,int x,int y){
    QString output("");
    for(int i = 0;i < 9;i++){
        for(int j = 0;j < 9;j++){
            if(x == i && y == j) output = output + "1 ";
            else output = output + "0 ";
        }
        if(i < 8) output += "\n";
    }
    radar_list[id]->setText(output);
}

void Widget::mapInterface(){
    this->repaint();
}

void Widget::testHit(){
    for(int i = 0;i < 10;i++){
        hitAction(rand()%16,1);
    }
}

void Widget::testRFID(){
    int id = rand()%4;
    for(int i = 0;i < 6;i++) rfid_data[id][i] = 3.0 + rand() % 3;
    rfidInterface(id,3);
}

void Widget::testradar(){
    int id = rand()%4;
    int x = rand()%9;
    int y = rand()%9;
    radarInterface(id,x,y);
}


void Widget::eraseHit(){
    for(int i = 0;i < 16;i++){
        count[i] = 0;
        attackCount_list[i]->setText(QString::number(count[i]));
    }
}
void Widget::eraseRFID(){
    QStandardItemModel* model = new QStandardItemModel();
    model->clear();
    for(int i = 0;i < 4;i++){
        RFID_list[i]->setModel(model);
        RFID_list[i]->show();
    }
}
void Widget::eraseradar(){
    for(int i = 0;i < 4;i++){
        radarInterface(i,10,10);
    }
}
void Widget::setButtonMap(){
    buttonMapper->setMapping(ui->bloodButton_red_1,0);
    buttonMapper->setMapping(ui->bloodButton_red_2,1);
    buttonMapper->setMapping(ui->bloodButton_blue_1,2);
    buttonMapper->setMapping(ui->bloodButton_blue_2,3);
    QObject::connect(ui->bloodButton_red_1, SIGNAL(clicked()), buttonMapper, SLOT(map()));
    QObject::connect(ui->bloodButton_red_2, SIGNAL(clicked()), buttonMapper, SLOT(map()));
    QObject::connect(ui->bloodButton_blue_1, SIGNAL(clicked()), buttonMapper, SLOT(map()));
    QObject::connect(ui->bloodButton_blue_2, SIGNAL(clicked()), buttonMapper, SLOT(map()));

    buttonMapper->setMapping(ui->velocityButton_red_1,4);
    buttonMapper->setMapping(ui->velocityButton_red_2,5);
    buttonMapper->setMapping(ui->velocityButton_blue_1,6);
    buttonMapper->setMapping(ui->velocityButton_blue_2,7);
    QObject::connect(ui->velocityButton_red_1, SIGNAL(clicked()), buttonMapper, SLOT(map()));
    QObject::connect(ui->velocityButton_red_2, SIGNAL(clicked()), buttonMapper, SLOT(map()));
    QObject::connect(ui->velocityButton_blue_1, SIGNAL(clicked()), buttonMapper, SLOT(map()));
    QObject::connect(ui->velocityButton_blue_2, SIGNAL(clicked()), buttonMapper, SLOT(map()));

    buttonMapper->setMapping(ui->commandLinkButton_red_1,8);
    buttonMapper->setMapping(ui->commandLinkButton_red_2,9);
    buttonMapper->setMapping(ui->commandLinkButton_blue_1,10);
    buttonMapper->setMapping(ui->commandLinkButton_blue_2,11);
    QObject::connect(ui->commandLinkButton_red_1, SIGNAL(clicked()), buttonMapper, SLOT(map()));
    QObject::connect(ui->commandLinkButton_red_2, SIGNAL(clicked()), buttonMapper, SLOT(map()));
    QObject::connect(ui->commandLinkButton_blue_1, SIGNAL(clicked()), buttonMapper, SLOT(map()));
    QObject::connect(ui->commandLinkButton_blue_2, SIGNAL(clicked()), buttonMapper, SLOT(map()));


    buttonMapper->setMapping(ui->bulletLinkButton_red_1,12);
    buttonMapper->setMapping(ui->bulletLinkButton_red_2,13);
    buttonMapper->setMapping(ui->bulletLinkButton_blue_1,14);
    buttonMapper->setMapping(ui->bulletLinkButton_blue_2,15);
    QObject::connect(ui->bulletLinkButton_red_1, SIGNAL(clicked()), buttonMapper, SLOT(map()));
    QObject::connect(ui->bulletLinkButton_red_2, SIGNAL(clicked()), buttonMapper, SLOT(map()));
    QObject::connect(ui->bulletLinkButton_blue_1, SIGNAL(clicked()), buttonMapper, SLOT(map()));
    QObject::connect(ui->bulletLinkButton_blue_2, SIGNAL(clicked()), buttonMapper, SLOT(map()));

    buttonMapper->setMapping(ui->sendRobotPosition_red_1,16);
    buttonMapper->setMapping(ui->sendRobotPosition_red_2,17);
    buttonMapper->setMapping(ui->sendRobotPosition_blue_1,18);
    buttonMapper->setMapping(ui->sendRobotPosition_blue_2,19);
    QObject::connect(ui->sendRobotPosition_red_1, SIGNAL(clicked()), buttonMapper, SLOT(map()));
    QObject::connect(ui->sendRobotPosition_red_2, SIGNAL(clicked()), buttonMapper, SLOT(map()));
    QObject::connect(ui->sendRobotPosition_blue_1, SIGNAL(clicked()), buttonMapper, SLOT(map()));
    QObject::connect(ui->sendRobotPosition_blue_2, SIGNAL(clicked()), buttonMapper, SLOT(map()));

    buttonMapper->setMapping(ui->sendRobotBlood_red_1,20);
    buttonMapper->setMapping(ui->sendRobotBlood_red_2,21);
    buttonMapper->setMapping(ui->sendRobotBlood_blue_1,22);
    buttonMapper->setMapping(ui->sendRobotBlood_blue_2,23);
    QObject::connect(ui->sendRobotBlood_red_1, SIGNAL(clicked()), buttonMapper, SLOT(map()));
    QObject::connect(ui->sendRobotBlood_red_2, SIGNAL(clicked()), buttonMapper, SLOT(map()));
    QObject::connect(ui->sendRobotBlood_blue_1, SIGNAL(clicked()), buttonMapper, SLOT(map()));
    QObject::connect(ui->sendRobotBlood_blue_2, SIGNAL(clicked()), buttonMapper, SLOT(map()));

    buttonMapper->setMapping(ui->bulletButton_red_1,24);
    buttonMapper->setMapping(ui->bulletButton_red_2,25);
    buttonMapper->setMapping(ui->bulletButton_blue_1,26);
    buttonMapper->setMapping(ui->bulletButton_blue_2,27);
    QObject::connect(ui->bulletButton_red_1, SIGNAL(clicked()), buttonMapper, SLOT(map()));
    QObject::connect(ui->bulletButton_red_2, SIGNAL(clicked()), buttonMapper, SLOT(map()));
    QObject::connect(ui->bulletButton_blue_1, SIGNAL(clicked()), buttonMapper, SLOT(map()));
    QObject::connect(ui->bulletButton_blue_2, SIGNAL(clicked()), buttonMapper, SLOT(map()));

    buttonMapper->setMapping(ui->wheelButton_red_1,28);
    buttonMapper->setMapping(ui->wheelButton_red_2,29);
    buttonMapper->setMapping(ui->wheelButton_blue_1,30);
    buttonMapper->setMapping(ui->wheelButton_blue_2,31);
    QObject::connect(ui->wheelButton_red_1, SIGNAL(clicked()), buttonMapper, SLOT(map()));
    QObject::connect(ui->wheelButton_red_2, SIGNAL(clicked()), buttonMapper, SLOT(map()));
    QObject::connect(ui->wheelButton_blue_1, SIGNAL(clicked()), buttonMapper, SLOT(map()));
    QObject::connect(ui->wheelButton_blue_2, SIGNAL(clicked()), buttonMapper, SLOT(map()));

    buttonMapper->setMapping(ui->shootButton_red_1,32);
    buttonMapper->setMapping(ui->shootButton_red_2,33);
    buttonMapper->setMapping(ui->shootButton_blue_1,34);
    buttonMapper->setMapping(ui->shootButton_blue_2,35);
    QObject::connect(ui->shootButton_red_1, SIGNAL(clicked()), buttonMapper, SLOT(map()));
    QObject::connect(ui->shootButton_red_2, SIGNAL(clicked()), buttonMapper, SLOT(map()));
    QObject::connect(ui->shootButton_blue_1, SIGNAL(clicked()), buttonMapper, SLOT(map()));
    QObject::connect(ui->shootButton_blue_2, SIGNAL(clicked()), buttonMapper, SLOT(map()));

    buttonMapper->setMapping(ui->moveButton_red_1,36);
    buttonMapper->setMapping(ui->moveButton_red_2,37);
    buttonMapper->setMapping(ui->moveButton_blue_1,38);
    buttonMapper->setMapping(ui->moveButton_blue_2,39);
    QObject::connect(ui->moveButton_red_1, SIGNAL(clicked()), buttonMapper, SLOT(map()));
    QObject::connect(ui->moveButton_red_2, SIGNAL(clicked()), buttonMapper, SLOT(map()));
    QObject::connect(ui->moveButton_blue_1, SIGNAL(clicked()), buttonMapper, SLOT(map()));
    QObject::connect(ui->moveButton_blue_2, SIGNAL(clicked()), buttonMapper, SLOT(map()));

    buttonMapper->setMapping(ui->modifyButton_red_1,40);
    buttonMapper->setMapping(ui->modifyButton_red_2,41);
    buttonMapper->setMapping(ui->modifyButton_blue_1,42);
    buttonMapper->setMapping(ui->modifyButton_blue_2,43);
    QObject::connect(ui->modifyButton_red_1, SIGNAL(clicked()), buttonMapper, SLOT(map()));
    QObject::connect(ui->modifyButton_red_2, SIGNAL(clicked()), buttonMapper, SLOT(map()));
    QObject::connect(ui->modifyButton_blue_1, SIGNAL(clicked()), buttonMapper, SLOT(map()));
    QObject::connect(ui->modifyButton_blue_2, SIGNAL(clicked()), buttonMapper, SLOT(map()));

    buttonMapper->setMapping(ui->allButton_red_1,44);
    buttonMapper->setMapping(ui->allButton_red_2,45);
    buttonMapper->setMapping(ui->allButton_blue_1,46);
    buttonMapper->setMapping(ui->allButton_blue_2,47);
    QObject::connect(ui->allButton_red_1, SIGNAL(clicked()), buttonMapper, SLOT(map()));
    QObject::connect(ui->allButton_red_2, SIGNAL(clicked()), buttonMapper, SLOT(map()));
    QObject::connect(ui->allButton_blue_1, SIGNAL(clicked()), buttonMapper, SLOT(map()));
    QObject::connect(ui->allButton_blue_2, SIGNAL(clicked()), buttonMapper, SLOT(map()));
}

void Widget::setShowMap(){
    for(int i = 0;i < 16;i++){
        count[i] = 0;
    }
    RFID_list[0] = ui->RFID_red_1;
    RFID_list[1] = ui->RFID_red_2;
    RFID_list[2] = ui->RFID_blue_1;
    RFID_list[3] = ui->RFID_blue_2;

    for(int i = 0;i < 4;i++){
        RFID_list[i]->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        RFID_list[i]->setAlternatingRowColors(true);
    }

    attack_list[0] = ui->attackup_red_1;
    attack_list[1] = ui->attackup_red_2;
    attack_list[2] = ui->attackup_blue_1;
    attack_list[3] = ui->attackup_blue_2;

    attack_list[4] = ui->attackright_red_1;
    attack_list[5] = ui->attackright_red_2;
    attack_list[6] = ui->attackright_blue_1;
    attack_list[7] = ui->attackright_blue_2;

    attack_list[8] = ui->attackdown_red_1;
    attack_list[9] = ui->attackdown_red_2;
    attack_list[10] = ui->attackdown_blue_1;
    attack_list[11] = ui->attackdown_blue_2;

    attack_list[12] = ui->attackleft_red_1;
    attack_list[13] = ui->attackleft_red_2;
    attack_list[14] = ui->attackleft_blue_1;
    attack_list[15] = ui->attackleft_blue_2;

    attackCount_list[0] = ui->attackLableup_red_1;
    attackCount_list[1] = ui->attackLableup_red_2;
    attackCount_list[2] = ui->attackLableup_blue_1;
    attackCount_list[3] = ui->attackLableup_blue_2;

    attackCount_list[4] = ui->attackLableright_red_1;
    attackCount_list[5] = ui->attackLableright_red_2;
    attackCount_list[6] = ui->attackLableright_blue_1;
    attackCount_list[7] = ui->attackLableright_blue_2;

    attackCount_list[8] = ui->attackLabledown_red_1;
    attackCount_list[9] = ui->attackLabledown_red_2;
    attackCount_list[10] = ui->attackLabledown_blue_1;
    attackCount_list[11] = ui->attackLabledown_blue_2;

    attackCount_list[12] = ui->attackLableleft_red_1;
    attackCount_list[13] = ui->attackLableleft_red_2;
    attackCount_list[14] = ui->attackLableleft_blue_1;
    attackCount_list[15] = ui->attackLableleft_blue_2;
    for(int i = 0;i < 16;i++)
        attack_list[i]->setStyleSheet("background-color: white;");

    radar_list[0] = ui->radar_red_1;
    radar_list[1] = ui->radar_red_2;
    radar_list[2] = ui->radar_blue_1;
    radar_list[3] = ui->radar_blue_2;

    button[0] = ui->allButton_red_1;
    button[1] = ui->allButton_red_2;
    button[2] = ui->allButton_blue_1;
    button[3] = ui->allButton_blue_2;

    states[0] = ui->stateLabel_red_1;
    states[1] = ui->stateLabel_red_2;
    states[2] = ui->stateLabel_blue_1;
    states[3] = ui->stateLabel_blue_2;

    eraseradar();

    for(int i = 0;i < 4;i++){
        b_list[i] = new BloodNewWindows(i);
        v_list[i] = new velocityNewWindows(i);
        // 默认摩擦轮轮子，射击和移动是0，就是不动的！
        wheel[i] = 0;
        shoot[i] = 0;
        move[i] = 0;
        start[i] = 0;
    }
}

void Widget::getBlood(){
    grpc::ClientContext context[4];
    r_.set_time(time(NULL));
    // blood
    for(int i = 0;i < 4;i++){
        status = stub_[i]->GetBlood(&(context[i]), r_, &(b_[i]));
        if (status.ok()) {
            b_list[i]->b = b_[i].blood();
            states[i]->setText("在线");
        }else {
            // std::cout << status.error_code() << ": " << status.error_message() << std::endl;
            states[i]->setText("离线");
        }
    }
}
void Widget::getBullet(){
    // bullet
    grpc::ClientContext context[4];
    r_.set_time(time(NULL));
    for(int i = 0;i < 4;i++){
        status = stub_[i]->GetBullet(&context[i], r_, &a_[i]);
        if (status.ok()) {
            bul[i] = a_[i].bullets();
        }else {
            // std::cout << status.error_code() << ": " << status.error_message() << std::endl;
        }
    }
}
void Widget::getPosture(){
    // printf("Try to get posture\n");
    // posture
    grpc::ClientContext context[4];
    r_.set_time(time(NULL));
    for(int i = 0;i < 4;i++){
        status = stub_[i]->GetPosture(&context[i], r_, &p_[i]);
        if (status.ok()) {
            double x = p_[i].x();
            double y = p_[i].y();
            // printf("get %f %f\n",x,y);
            m->updatePosition(i,x,y);
            mapInterface();
        }else {
            // std::cout << status.error_code() << ": " << status.error_message() << std::endl;
        }
    }
}
void Widget::getGunposture(){
    // gunposture
    grpc::ClientContext context[4];
    r_.set_time(time(NULL));
    for(int i = 0;i < 4;i++){
        status = stub_[i]->GetGimbalYaw(&context[i], r_, &g_[i]);
        if (status.ok()) {
            // unfinished
        }else {
            // std::cout << status.error_code() << ": " << status.error_message() << std::endl;
        }
    }
}
void Widget::getVelocity(){
    // velocity
    grpc::ClientContext context[4];
    r_.set_time(time(NULL));
    for(int i = 0;i < 4;i++){
        status = stub_[i]->GetVelocity(&context[i], r_, &v_[i]);
        if (status.ok()) {
            v_list[i]->v = sqrt(v_[i].velocity_linear_x() * v_[i].velocity_linear_x() + v_[i].velocity_linear_y() * v_[i].velocity_linear_y());
        }else {
            // std::cout << status.error_code() << ": " << status.error_message() << std::endl;
        }
    }
}
void Widget::getAffected(){
    // affected
    grpc::ClientContext context[4];
    r_.set_time(time(NULL));
    for(int i = 0;i < 4;i++){
        status = stub_[i]->GetAttacked(&context[i], r_, &aff_[i]);
        if (status.ok()) {
            hitAction(i*4+0,aff_[i].up());
            hitAction(i*4+1,aff_[i].left());
            hitAction(i*4+2,aff_[i].down());
            hitAction(i*4+3,aff_[i].right());
        }else {
            // std::cout << status.error_code() << ": " << status.error_message() << std::endl;
        }
    }
}
void Widget::getObjectDection(){
    // object
    grpc::ClientContext context[4];
    r_.set_time(time(NULL));
    for(int i = 0;i < 4;i++){
        status = stub_[i]->GetObjectDection(&context[i], r_, &obj_[i]);
        if (status.ok()) {
            // TODO:这里需要一个数据：整个摄像机的大小，我这里假设是100了
            // 暂时没搞清楚repeat的意思

            auto x1_list = obj_[i].x1();
            auto x2_list = obj_[i].x2();
            auto y1_list = obj_[i].y1();
            auto y2_list = obj_[i].y2();
            // int size = x1.size();
            for (int i = 0; i < 1; i++) {
                const float x1 = x1_list.Get(i);
                const float x2 = x2_list.Get(i);
                const float y1 = y1_list.Get(i);
                const float y2 = y2_list.Get(i);
                rfid_data[i][0] = x1;
                rfid_data[i][1] = y1;
                rfid_data[i][2] = x2;
                rfid_data[i][3] = y2;
                rfidInterface(i,2);
                double x = (x1 + x2) / 2;
                double y = (y1 + y2) / 2;
                int p = x * 9 / 100;
                int q = y * 9 / 100;
                radarInterface(i,p,q);
                  //const std::float& description = descs.Get(i);
                  std::cout << "get success: " << x1 << std::endl;
            }
            return;

            /*
            float x1 = obj_[i].x1();
            float x2 = obj_[i].x2();
            float y1 = obj_[i].y1();
            float y2 = obj_[i].y2();
            rfid_data[i][0] = x1;
            rfid_data[i][1] = y1;
            rfid_data[i][2] = x2;
            rfid_data[i][3] = y2;
            rfidInterface(i,2);
            double x = (x1 + x2) / 2;
            double y = (y1 + y2) / 2;
            int p = x * 9 / 100;
            int q = y * 9 / 100;
            radarInterface(i,p,q);
            */

        }else {
            // std::cout << status.error_code() << ": " << status.error_message() << std::endl;
        }
    }
}

void Widget::slotTimeout(){
    getBlood();
    getBullet();
    getPosture();
    getGunposture();
    getVelocity();
    getAffected();
    getObjectDection();
}

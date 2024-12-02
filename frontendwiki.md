### 自主对战平台前端wiki

需要完成的后端操作：

```
service RobotComm{
    //向服务器索取血量信息 传回血量信息
    rpc GetBlood(Request) returns (Blood) {}
    //向服务器索取弹药量信息 传回弹药量信息
    rpc GetAmmunition(Request) returns (Ammunition) {}
    //向服务器索取位姿信息 传回位姿信息
    rpc GetPosture(Request) returns (Posture) {}
    //向服务器索取枪口朝向信息 传回枪口朝向信息
    rpc GetGunPosture(Request) returns (GunPosture) {}
    //向服务器索取速度信息 传回速度信息
    rpc GetVelocity(Request) returns (Velocity) {}
    //向服务器索取受击信息 传回受击信息
    rpc GetAffected(Request) returns (Affected) {}
    //向服务器索取位置信息 传回位置信息
    rpc GetObjectDection(Request) returns (ObjectDection) {}

    //向服务器传输血量信息 传回是否正确设置
    rpc PostBlood(Blood) returns(Response) {}
    //向服务器传输弹药量信息 传回是否正确设置
    rpc PostAmmunition(Ammunition) returns(Response) {}
    //向服务器传输目的地信息 传回是否正确设置
    rpc PostDestination(Destination) returns(Response) {}
    //向服务器传输摩擦轮信息 传回是否正确设置
    rpc PostFrictionWheel(FrictionWheel) returns(Response) {}
    //向服务器传输停止信息 传回是否正确设置
    rpc PostStop(Stop) returns(Response) {}
    //向服务器传输子弹开关信息 传回是否正确设置
    rpc PostBullet(Bullet) returns(Response) {}
}
```
相关数据结构

```
message Request{
    float time = 1;//都是为了记录时间戳，下同
}

message Blood{
    int32 blood = 1;//记录血量
    float time = 2;
}

message Ammunition{
    int32 ammunition = 1;//记录弹药信息
    int32 type = 2;//当用于GetAmmunition函数时可忽略，当用于PostAmmunition函数时，1是+，2是-，3是设置为某个值
    float time = 3;
}

message Posture{
    float x = 1;//位置的x坐标
    float y = 2;//位置的Y坐标
    float radian = 3;//底盘的朝向，弧度制
    float time = 4;
}

message GunPosture{
    float radian = 1;//枪口的朝向，弧度制
    float time = 2;
}

message Velocity{
    float velocity = 1;//速度的值
    float time = 2;
}

message Affected{
    int32 up = 1;//上方装甲板受击次数
    int32 down = 2;
    int32 left = 3;
    int32 right = 4;
    float time = 5;
}

message ObjectDection{
    repeated float x1 = 1;//摄像头目标检测的框，左上角的点的x坐标
    repeated float y1 = 2;//左上角的点的y坐标
    repeated float x2 = 3;//右下
    repeated float y2 = 4;
    float time = 5;
}

message Response{
    float time = 1;
}

message Destination{
    float x = 1;//目的地的x坐标
    float y = 2;
    float time = 3;
}

message FrictionWheel{
    bool flag = 1;//true为打开摩擦轮
    float time = 2;
}

message Stop{
    bool flag = 1;//true为不停止
    float time = 2;
}

message Bullet{
    bool flag = 1;//true为打开子弹开关
    float time = 2;
}
```
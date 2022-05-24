#ifndef COMMON_DEFS_H
#define COMMON_DEFS_H

static const int WinWidth=480;
static const int WinHeight=700;
static const int SelfBulletMoveSpeed=10;//友机子弹移动速度
static const int SelfBulletMoveInterval=100;//友机子弹隔多久移动一次
static const int SelfBulletCount=10;//友机左\右子弹数量
static const int SelfBulletSpawnInterval=300;//友机子弹产出间隔时间(毫秒)
static const int BgMoveSpeed=1;//背景图片移动速度
static const int Enemy1Speed=20;//敌机1移动速度
static const int Enemy1Interval=100;//敌机1隔多久移动一次
static const int Enemy1Count=5;//敌机1数量
static const int CollideInterval=30;//间隔多久进行一次碰撞检测(毫秒)
static const int Enemy1ChangeImgInterval=30;
static const int Enemy1DownImgCount=4;
static const int Enemy3ShowY=3;//敌机3出现时的y坐标
static const int Enemy3MoveXSpeed=3;//敌机3横向移动速度
static const int Enemy3MoveYSpeed=10;
static const int Enemy3MoveInterval=100;
static const int Enemy3ImgInterval=100;
static const int Enemy3ImgCount=2;
static const int Enemy3AttackInterval=1000;//Enemy3产生炮弹(即Enemy1)的间隔
static const int Enemy3AttackCount=3;//炮弹数量
static const int Enemy3AttackYOffset=30;//发射炮弹,炮弹的y坐标偏移
static const int Enemy3Blood=100;//敌机3血条
static const int Enemy3BloodOffset=1;//敌机3减血幅度
static const int Enemy3DownImgCount=6;//敌机3被击落时的图片数量
static const int Enemy3DownImgInterval=200;//敌机3被击落时图片切换间隔

static const char* MyPlane1Img=":/resources/me1.png";
static const char* SelfBulletImg=":/resources/bullet1.png";
static const char* BackgroundImg=":/resources/background.png";
static const char* BackGroundMusic=":/resources/background.wav";
static const char* Enemy1Img=":/resources/enemy1.png";
static const char* Enemy1DownImg=":/resources/enemy1_down%1.png";
static const char* DownMusic=":/resources/down.wav";
static const char* Enemy3Img=":/resources/enemy3_n%1.png";
static const char* Enemy3DownImg=":/resources/enemy3_down%1.png";

#endif // COMMON_DEFS_H

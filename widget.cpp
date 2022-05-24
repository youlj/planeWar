#include "widget.h"
#include"common_defs.h"
#include"myPlane.h"
#include"selfBullet.h"
#include"enemy1.h"
#include"enemy3.h"

#include<QGraphicsScene>
#include<QMouseEvent>
#include<QTimer>
#include<QPainter>
#include<QSound>

#include<QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(WinWidth,WinHeight);
    QGraphicsScene*scene=new QGraphicsScene(QRectF(0,0,width(),height()));
    view_=new View(scene,this);
    view_->setStyleSheet("background:transparent;");//需要背景透明(不然背景图片显示不出来)
    scene->setParent(view_);
    bgImg.load(BackgroundImg);
    my_plane=new MyPlane(scene);

    bgTimer=new QTimer(this);
    connect(bgTimer,&QTimer::timeout,[this]()
    {
        //调用paintEvent,背景移动,有个bug,当鼠标拖动飞机时会加速移动,????
        update();
    });
    bgTimer->start(100);

    //友机发射子弹(急待改进,影响游戏体验...)
    selfBulletTimer=new QTimer(this);
    connect(selfBulletTimer,&QTimer::timeout,[this]()
    {
        static int i=0;
        if(++i>SelfBulletCount)
        {
            selfBulletTimer->stop();//不再产出额外子弹(左右各SelfBulletCount发子弹)
        }
        selfBulletVec.emplace_back(new SelfBullet(my_plane));// 左子弹
        selfBulletVec.emplace_back(new SelfBullet(my_plane,false));//右子弹
    });
    selfBulletTimer->start(SelfBulletSpawnInterval);

    //生成敌机1
    for(int i=0;i<Enemy1Count;++i)
    {
        enemy1Vec.emplace_back(new Enemy1(scene));
    }

    //生成敌机3
    enemy3_=new Enemy3(scene);

    collideTimer=new QTimer(this);
    connect(collideTimer,&QTimer::timeout,[this]()
    {
        //碰撞检测(可以优化的吧...)
        for(auto& selfBullet:selfBulletVec)
        {
            //敌机1
            for(auto& enemy1:enemy1Vec)
            {
                if(selfBullet->sceneBoundingRect().intersects(enemy1->sceneBoundingRect()))
                {
                    //QSound::play(DownMusic);//播放碰撞音乐时画面稍显卡顿,????
                    selfBullet->setPosition();//复位
                    enemy1->moveTimer->stop();
                    enemy1->changeImgTimer->start(Enemy1ChangeImgInterval);
                }
            }

            //敌机3
            if(selfBullet->sceneBoundingRect().intersects(enemy3_->sceneBoundingRect()))
            {
                selfBullet->setPosition();
                enemy3_->blood-=Enemy3BloodOffset;
                if(enemy3_->blood<=0)
                {
                    enemy3_->moveTimer->stop();
                    enemy3_->imgTimer->stop();
                    enemy3_->downImgTimer->start(Enemy3DownImgInterval);
                }
            }

            //敌机3发射出去的敌机1
            for(auto& enemy1:enemy3_->enemy1Vec)
            {
                if(selfBullet->sceneBoundingRect().intersects(enemy1->sceneBoundingRect()))
                {
                    selfBullet->setPosition();
                    enemy1->moveTimer->stop();
                    enemy1->changeImgTimer->start(Enemy1ChangeImgInterval);
                }
            }
        }
    });
    collideTimer->start(CollideInterval);

    QSound*bgSound=new QSound(BackGroundMusic,this);
    bgSound->setLoops(QSound::Infinite);//无限循环
    bgSound->play();
}

Widget::~Widget()
{
}

Widget* Widget::getInstance()
{
    static Widget widget;
    return &widget;
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(QRect(0,0,width(),height()),bgImg,QRect(0,bgY,width(),height()));
    if(bgImg.height()-bgY<height())//填补空白
    {
        painter.drawImage(QRect(0,bgImg.height()-bgY,width(),height()-(bgImg.height()-bgY)),
                          bgImg,QRect(0,0,width(),height()-(bgImg.height()-bgY)));
    }
    if((bgY+=BgMoveSpeed)>bgImg.height())//重头开始
    {
        bgY=0;
    }
}

void Widget::View::mouseMoveEvent(QMouseEvent *event)
{
    static bool flag=true;
    if(flag)
    {
        planeWidth=Widget::getInstance()->my_plane->boundingRect().width();
        planeHeight=Widget::getInstance()->my_plane->boundingRect().height();
        flag=false;
    }

    //边界控制(加了边界控制后移动飞机当靠近边界时有点不灵活了,????)
    if(event->x()-planeWidth/2<0||event->x()+planeWidth/2>width()
            ||event->y()-planeHeight/2<0||event->y()+planeHeight/2>height())
    {
        return;
    }

    Widget::getInstance()->my_plane->setPosition(event->x(),event->y());
}

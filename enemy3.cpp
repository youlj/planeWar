#include "enemy3.h"
#include"common_defs.h"
#include"enemy1.h"

#include<QGraphicsScene>
#include<QTime>
#include<QTimer>
#include<QImage>
#include<QPainter>

#include<QDebug>

Enemy3::Enemy3(QGraphicsScene*scene):blood{Enemy3Blood},scene_{scene}
{
    scene->addItem(this);
    setParent(scene);
    img.load(QString(Enemy3Img).arg(1));
    qsrand(QTime::currentTime().msec());
    setPos((qrand()%((int)(scene->width()/2-img.width()/2))),-qrand()%((int)(scene->height()/2)));

    moveTimer=new QTimer(this);
    connect(moveTimer,&QTimer::timeout,[this]()
    {
        if(mapToScene(pos()).y()>=Enemy3ShowY)
        {
            setY(Enemy3ShowY);
            if(moveLeft)
            {
                moveBy(-Enemy3MoveXSpeed,0);
                if(mapToScene(pos()).x()<=0)//移到最左边了,往右移动
                {
                    moveLeft=false;
                }
            }
            else
            {
                moveBy(Enemy3MoveXSpeed,0);
                if(mapToScene(pos()).x()>=(scene_->width()-img.width()))//移到最右边了,往左移动
                {
                    moveLeft=true;
                }
            }
        }
        else//向下移动,出现在场景中
        {
            moveBy(0,Enemy3MoveYSpeed);
        }
    });
    moveTimer->start(Enemy3MoveInterval);

    //切换正常图片
    imgTimer=new QTimer(this);
    connect(imgTimer,&QTimer::timeout,[this]()
    {
        static int i=0;
        img.load(QString(Enemy3Img).arg(i%Enemy3ImgCount+1));
        if(++i==Enemy3ImgCount)
        {
            i=0;
        }
    });
    imgTimer->start(Enemy3ImgInterval);

    downImgTimer=new QTimer(this);
    connect(downImgTimer,&QTimer::timeout,[this]()
    {
        static int i=0;
        img.load(QString(Enemy3DownImg).arg(++i));
        if(i==Enemy3DownImgCount)//已经切换到最后一张被击中时的图片了,重头开始吧
        {
            setPos((qrand()%((int)(scene_->width()/2-img.width()/2))),-qrand()%((int)(scene_->height()/2)));
            img.load(QString(Enemy3Img).arg(1));
            i=0;
            blood=Enemy3Blood;
            moveTimer->start(Enemy3MoveInterval);
            imgTimer->start(Enemy3ImgInterval);
            downImgTimer->stop();
        }
    });

    //发射炮弹(即敌机1)
    attckTimer=new QTimer(this);
    connect(attckTimer,&QTimer::timeout,[this]()
    {
        static int i=0;
        enemy1Vec.emplace_back(new Enemy1(scene_,this));
        if(++i==Enemy3AttackCount)
        {
            attckTimer->stop();//停止产生炮弹
        }
    });
    attckTimer->start(Enemy3AttackInterval);
}

QRectF Enemy3::boundingRect() const
{
    return QRectF(pos().x(),pos().y(),img.width(),img.height());
}

void Enemy3::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawImage(boundingRect(),img);
}

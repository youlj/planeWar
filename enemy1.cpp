#include "enemy1.h"
#include"common_defs.h"
#include"enemy3.h"

#include<QGraphicsScene>
#include<QTimer>
#include<QTime>
#include<QPainter>

Enemy1::Enemy1(QGraphicsScene*scene,Enemy3*enemy3):scene_{scene},enemy3_{enemy3}
{
    scene->addItem(this);
    setParent(scene);
    img.load(Enemy1Img);
    qsrand(QTime::currentTime().msec());
    if(!enemy3_)
    {
        setPos((qrand()%((int)(scene->width()/2-img.width()/2))),-qrand()%((int)(scene->height()/2)));
    }
    else//作为enemy3发射出去的炮弹(Enemy1类中不应该有Enemy3的,这样耦合性太大了,待改进)
    {
        //首先说明一点,图元在场景中的坐标是场景坐标的一半,即如果场景的坐标为(10,10),则图元的坐标为(5,5)
        //即图元pos()为(5,5),切换成场景坐标mapToScene(pos())为(10,10)
        setPos(enemy3_->pos().x()+enemy3_->boundingRect().width()/4-img.width()/4,
               enemy3_->pos().y()+enemy3_->boundingRect().height()/2-Enemy3AttackYOffset);
    }

    moveTimer=new QTimer(this);
    connect(moveTimer,&QTimer::timeout,[this]()
    {
        if(mapToScene(pos()).y()>scene_->height())//飞到最底下了,需要重新放置
        {
            if(!enemy3_)
            {
                setPos((qrand()%((int)(scene_->width()/2-img.width()/2))),-qrand()%((int)(scene_->height()/2)));
            }
            else
            {
                setPos(enemy3_->pos().x()+enemy3_->boundingRect().width()/4-img.width()/4,
                       enemy3_->pos().y()+enemy3_->boundingRect().height()/2-Enemy3AttackYOffset);
            }
        }
        moveBy(0,Enemy1Speed);//x坐标不变,y增加(向下移动)
    });
    moveTimer->start(Enemy1Interval);

    changeImgTimer=new QTimer(this);
    connect(changeImgTimer,&QTimer::timeout,[this]()
    {
        static int i=0;
        img.load(QString(Enemy1DownImg).arg(++i));
        if(i==Enemy1DownImgCount)//已经切换到最后一张被击中时的图片了,重头开始吧
        {
            if(!enemy3_)
            {
                setPos((qrand()%((int)(scene_->width()/2-img.width()/2))),-qrand()%((int)(scene_->height()/2)));
            }
            else
            {
                setPos(enemy3_->pos().x()+enemy3_->boundingRect().width()/4-img.width()/4,
                       enemy3_->pos().y()+enemy3_->boundingRect().height()/2-Enemy3AttackYOffset);
            }
            img.load(Enemy1Img);
            i=0;
            moveTimer->start(Enemy1Interval);
            changeImgTimer->stop();
        }
    });
}

QRectF Enemy1::boundingRect() const
{
    return QRectF(pos().x(),pos().y(),img.width(),img.height());
}

void Enemy1::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawImage(boundingRect(),img);
}

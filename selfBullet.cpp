#include "selfBullet.h"
#include"common_defs.h"

#include<QGraphicsScene>
#include<QPainter>
#include<QPropertyAnimation>
#include<QTimer>

#include<QDebug>

SelfBullet::SelfBullet(QGraphicsObject *planeItem,bool isLeft):plane_{planeItem},isLeft_{isLeft},
    moveSpeed{SelfBulletMoveSpeed}
{
    planeItem->scene()->addItem(this);
    setParent(planeItem->scene());
    img_.load(SelfBulletImg);
    //setCacheMode(QGraphicsItem::ItemCoordinateCache);
    setPosition();

    moveTimer=new QTimer(this);
    connect(moveTimer,&QTimer::timeout,[this]()
    {
        if(mapToScene(pos()).y()<-img_.height())//子弹出去了
        {
            //更新x,y坐标(以飞机为参照点)
            if(isLeft_)//左子弹
            {
                x_=plane_->x()+plane_->boundingRect().width()/6+plane_->boundingRect().x();
            }
            else//右子弹
            {
                x_=plane_->x()+plane_->boundingRect().width()-plane_->boundingRect().width()/5+plane_->boundingRect().x();
            }
            y_=plane_->y()+plane_->boundingRect().height()/4+plane_->boundingRect().y();
            setX(x_/2);
            setY(y_/2);
        }
        moveBy(0,-SelfBulletMoveSpeed);//x坐标不变,y坐标向上移动(调用paint刷新)
    });
    moveTimer->start(SelfBulletMoveInterval);

}

QRectF SelfBullet::boundingRect() const
{
    return QRectF(pos().x(),pos().y(),img_.width(),img_.height());
}

void SelfBullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawImage(boundingRect(),img_);
}

void SelfBullet::setPosition()
{
    //相对于飞机的坐标
    if(isLeft_)//左子弹
    {
        x_=plane_->x()+plane_->boundingRect().width()/6+plane_->boundingRect().x();
    }
    else//右子弹
    {
        x_=plane_->x()+plane_->boundingRect().width()-plane_->boundingRect().width()/5+plane_->boundingRect().x();
    }
    y_=plane_->y()+plane_->boundingRect().height()/4+plane_->boundingRect().y();
    setPos(x_/2,y_/2);//坐标需要转换(试了好久,靠)
}

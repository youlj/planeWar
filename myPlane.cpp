#include "myPlane.h"
#include"common_defs.h"

#include<QPainter>
#include<QGraphicsScene>

#include<QDebug>

MyPlane::MyPlane(QGraphicsScene*scene):scene_{scene}
{
    scene->addItem(this);
    setParent(scene);
    img_.load(MyPlane1Img);
}

QRectF MyPlane::boundingRect() const
{
    return QRectF(scene_->width()/2-img_.width()/2,scene_->height()-img_.height(),
                  img_.width(),img_.height());
}

void MyPlane::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawImage(boundingRect(),img_);
}

void MyPlane::setPosition(int x, int y)
{
    setPos(QPointF(x-(scene_->width()/2),y-(scene_->height()-img_.height()/2)));
}

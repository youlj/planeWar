#ifndef ENEMY1_H
#define ENEMY1_H

#include<QGraphicsObject>

class Enemy3;

class Enemy1 : public QGraphicsObject
{
public:
    Enemy1(QGraphicsScene*scene,Enemy3*enemy3=nullptr);

    //必须要重写的纯虚函数
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

public:
    QTimer*moveTimer=nullptr;
    QTimer* changeImgTimer=nullptr;//被击中时切换图片

private:
    QGraphicsScene*scene_=nullptr;
    QImage img;
    Enemy3*enemy3_=nullptr;
};

#endif // ENEMY1_H

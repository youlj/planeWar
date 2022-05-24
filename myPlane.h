#ifndef MYPLANE_H
#define MYPLANE_H

#include<QGraphicsObject>

//操纵的飞机
class MyPlane : public QGraphicsObject
{
public:
    MyPlane(QGraphicsScene*scene);

    //必须要重写的纯虚函数
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    void setPosition(int x,int y);

private:
    QGraphicsScene*scene_=nullptr;
    QImage img_;
};

#endif // MYPLANE_H

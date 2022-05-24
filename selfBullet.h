#ifndef SELFBULLET_H
#define SELFBULLET_H

#include<QGraphicsObject>

class QPropertyAnimation;

//自己飞机发出去的子弹
class SelfBullet : public QGraphicsObject
{
public:
    //第二个参数表示子弹是否位于飞机左边(飞机两边都发射子弹)
    SelfBullet(QGraphicsObject*planeItem,bool isLeft=true);

    //必须要重写的纯虚函数
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    void setPosition();

private:
    QImage img_;
    QGraphicsObject*plane_=nullptr;
    bool isLeft_;
    QTimer*moveTimer=nullptr;
    int moveSpeed=0;
    int x_=0;//x坐标
    int y_=0;//y坐标
};

#endif // SELFBULLET_H

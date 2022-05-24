#ifndef ENEMY3_H
#define ENEMY3_H

#include<QGraphicsObject>
#include<vector>

class Enemy1;

class Enemy3 : public QGraphicsObject
{
public:
    Enemy3(QGraphicsScene*scene);

    //必须要重写的纯虚函数
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

public:
    QTimer* moveTimer=nullptr;
    QTimer* imgTimer=nullptr;//正常图片切换
    QTimer* downImgTimer=nullptr;//被击落时图片切换
    std::vector<Enemy1*>enemy1Vec;
    int blood=0;

private:
    QGraphicsScene*scene_=nullptr;
    QImage img;
    bool moveLeft=false;//刚开始横向往右移动
    QTimer*attckTimer=nullptr;//发射炮弹用(炮弹即Enemy1)
};

#endif // ENEMY3_H

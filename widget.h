#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QGraphicsView>
#include<vector>

class MyPlane;
class Enemy1;
class SelfBullet;
class Enemy3;

class Widget : public QWidget
{
    Q_OBJECT
private:
    Widget(QWidget *parent = nullptr);
public:
    ~Widget();
    static Widget* getInstance();//单例,为了让嵌套类(View)访问my_plane

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    class View:public QGraphicsView
    {
    public:
        View(QGraphicsScene*scene,QWidget*parent):QGraphicsView(scene,parent){}
    protected:
        //外层类重写鼠标移动事件无效(会被QGraphicsView覆盖掉),所以写个嵌套类
        void mouseMoveEvent(QMouseEvent *event) override;
    private:
        int planeWidth=0;
        int planeHeight=0;
    };

private:
    MyPlane* my_plane=nullptr;
    View* view_=nullptr;
    QTimer* selfBulletTimer=nullptr;//用于发射出一系列子弹
    QTimer* bgTimer=nullptr;//管理背景图片移动
    QTimer* collideTimer;//碰撞检测
    QImage bgImg;//背景图片
    int bgY=0;//背景图片y坐标
    std::vector<Enemy1*>enemy1Vec;
    std::vector<SelfBullet*>selfBulletVec;
    Enemy3*enemy3_=nullptr;
};
#endif // WIDGET_H

#ifndef PLANE_H
#define PLANE_H
#include <QPixmap>
#include <QRect>
#include "bullet.h"

class Plane
{
public:
    Plane();

    //发射子弹
    void shoot();

    //设置飞机位置
    void setPositon(int x,int y);

    //飞机资源、对象
    QPixmap plane;

    //飞机坐标
    int m_X;
    int m_Y;

    //飞机的矩形边框
    QRect m_Rect;

    //弹匣
    Bullet m_bullets[BULLET_NUM];

    //发射间隔记录
    int m_recorder=0;
};

#endif // PLANE_H

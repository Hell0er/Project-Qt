#include "plane.h"
#include "config.h"

Plane::Plane()
{
    //初始化加载飞机图片资源
    plane.load(PLANE_PATH);

    //初始化飞机坐标
    m_X=(GAME_WIDTH-plane.width())/2;
    m_Y=GAME_HEIGHT-plane.height();

    //初始化矩形边框
    m_Rect.setHeight(plane.height());
    m_Rect.setWidth(plane.width());
    m_Rect.moveTo(m_X,m_Y);

    for (int i=0;i<BULLET_NUM;i++)
    {
        m_bullets[i].m_free=true;
    }
}

void Plane::setPositon(int x, int y)
{
    m_X=x;
    m_Y=y;
    m_Rect.moveTo(m_X,m_Y);
}

void Plane::shoot()
{
    //累加时间间隔记录变量
    m_recorder++;

    //如果记录的数字未达到发射子弹时间间隔，直接return，不发射子弹
    if (m_recorder<BULLET_INTERVAL)
    {
        return;
    }
    else   //达到发射时间
    {
        m_recorder=0;

        //发射子弹
        for (int i=0;i<BULLET_NUM;i++)
        {
            //如果是空闲子弹，发射
            if (m_bullets[i].m_free)
            {
                //更改空闲状态
                m_bullets[i].m_free=false;

                //设置子弹坐标
                m_bullets[i].m_X=m_X+m_Rect.width()/2;
                m_bullets[i].m_Y=m_Y-5;
                break;
            }
        }
    }
}

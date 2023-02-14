#include "bullet.h"

Bullet::Bullet()
{
    //加载子弹资源
    m_bullet.load(BULLET_PATH);

    //子弹坐标
    m_X=GAME_WIDTH/2-m_bullet.width()/2;
    m_Y=GAME_HEIGHT;

    //子弹状态
    m_speed=BULLET_SPEED;

    //子弹边框
    m_Rect.setWidth(m_bullet.width());
    m_Rect.setHeight(m_bullet.height());
    m_Rect.moveTo(m_X,m_Y);
}

void Bullet::updatePosition()
{
    //空闲状态下的子弹，不需要计算坐标
    if (m_free)
    {
        return;
    }
    else   //子弹向上移动
    {
        m_Y-=m_speed;
        m_Rect.moveTo(m_X,m_Y);


        //子弹位置超出窗口
        if (m_Y<=-m_Rect.height())
        {
            m_free=true;
        }
    }
}

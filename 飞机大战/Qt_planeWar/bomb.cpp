#include "bomb.h"

Bomb::Bomb()
{
    //将所有爆炸的pixmap放入数组
    for (int i=1;i<=BOMB_MAX;i++)
    {
        //str 类似于 ":/images/enemy2_down%1.png"
        QString str=QString(BOMB_PATH).arg(i);
        m_pixArr.push_back(QPixmap(str));
    }

    //坐标
    m_X=0;
    m_Y=0;

    //空闲状态
    m_free=true;

    //当前播放图片的下标
    m_index=0;

    //播放爆炸间隔记录
    m_recorder=0;
}

void Bomb::updateInfo()
{
    //空闲状态下爆炸效果，return
    if (m_free)
    {
        return;
    }
    m_recorder++;

    //如果记录爆炸的时间未到达爆炸的间隔，不需要切图，直接return
    if (m_recorder<BOMB_INTERVAL)
    {
        return;
    }

    //重置记录
    m_recorder=0;

    //切换爆炸播放的图片的下标
    m_index++;

    if (m_index>BOMB_MAX-1)
    {
        m_index=0;
        m_free=true;
    }
}

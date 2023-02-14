#include "mainscene.h"
#include "config.h"
#include <QIcon>
#include <QPainter>
#include "map.h"
#include "plane.h"
#include <QMouseEvent>
#include <QDebug>
#include <ctime>

MainScene::MainScene(QWidget *parent)   //构造函数
    : QWidget(parent)
{
    //调用初始化场景
    initScene();

    //调用启动游戏
    playGame();
}

MainScene::~MainScene()   //析构函数
{

}

void MainScene::initScene()   //初始化场景
{
    //设置窗口固定尺寸
    setFixedSize(GAME_WIDTH,GAME_HEIGHT);

    //设置标题
    setWindowTitle(GAME_TITLE);

    //加载图标
    setWindowIcon(QIcon(GAME_ICON));

    //定时器设置
    m_timer.setInterval(GAME_RATE);

    //敌机出场的时间间隔初始化
    m_recorder=0;

    //随机数种子
    srand((unsigned int)time(NULL));
}

void MainScene::playGame()   //启动游戏
{
    //启动定时器
    m_timer.start();

    //监听定时发送的信号
    connect(&m_timer,&QTimer::timeout,[=](){
        //敌机出场
        enemyToScene();

        //更新游戏中元素的坐标
        upDatePosition();

        //绘制到屏幕中
        update();

        //碰撞检测
        collisionDetection();
    });
}

void MainScene::upDatePosition()
{
    //更新地图坐标
    m_map.mapPosition();

    //发射子弹
    m_plane.shoot();

    //所有非空闲子弹的当前坐标
    for (int i=0;i<BULLET_NUM;i++)
    {
        //如果非空闲，计算发射位置
        if (!m_plane.m_bullets[i].m_free)
        {
            m_plane.m_bullets[i].updatePosition();
        }
    }

    //敌机出场
    for (int i=0;i<ENEMY_NUM;i++)
    {
        //如果非空闲，计算坐标
        if (!m_enemys[i].m_free)
        {
            m_enemys[i].updatePosition();
        }
    }

    //计算爆炸图片
    for (int i=0;i<BOMB_NUM;i++)
    {
        if (!m_bombs[i].m_free)
        {
            m_bombs[i].updateInfo();
        }
    }
}

void MainScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    //绘制地图
    painter.drawPixmap(0,m_map.m_map1_posY,m_map.m_map1);
    painter.drawPixmap(0,m_map.m_map2_posY,m_map.m_map2);

    //绘制英雄飞机
    painter.drawPixmap(m_plane.m_X,m_plane.m_Y,m_plane.plane);

    //绘制子弹
    for (int i=0;i<BULLET_NUM;i++)
    {
        //如果非空闲，绘制
        if (!m_plane.m_bullets[i].m_free)
        {
            painter.drawPixmap(m_plane.m_bullets[i].m_X,m_plane.m_bullets[i].m_Y,m_plane.m_bullets[i].m_bullet);
        }
//        qDebug()<<i<<","<<m_plane.m_bullets[i].m_free<<","<<m_plane.m_bullets[i].m_X<<","<<m_plane.m_bullets[i].m_Y;
//        painter.drawPixmap(m_plane.m_bullets[i].m_X,m_plane.m_bullets[i].m_Y,m_plane.m_bullets[i].m_bullet);
    }

    //绘制敌机
    for (int i=0;i<ENEMY_NUM;i++)
    {
        //如果非空闲，绘制
        if (!m_enemys[i].m_free)
        {
            painter.drawPixmap(m_enemys[i].m_X,m_enemys[i].m_Y,m_enemys[i].m_enemy);
        }
    }

    //绘制爆炸
    for (int i=0;i<BOMB_NUM;i++)
    {
        if (!m_bombs[i].m_free)
        {
            painter.drawPixmap(m_bombs[i].m_X,m_bombs[i].m_Y,
                               m_bombs[i].m_pixArr[m_bombs[i].m_index]);
        }
    }
}

void MainScene::mouseMoveEvent(QMouseEvent *event)
{
    int x=event->x()-m_plane.m_Rect.width()/2;
    int y=event->y()-m_plane.m_Rect.height()/2;

    //边界检测
    if (x<=0)
    {
        x=0;
    }
    if (x>=GAME_WIDTH-m_plane.m_Rect.width())
    {
        x=GAME_WIDTH-m_plane.m_Rect.width();
    }
    if (y<=0)
    {
        y=0;
    }
    if (y>=GAME_HEIGHT-m_plane.m_Rect.height())
    {
        y=GAME_HEIGHT-m_plane.m_Rect.height();
    }

    m_plane.setPositon(x,y);
}

void MainScene::enemyToScene()
{
    m_recorder++;

    //未达到出场间隔
    if (m_recorder<ENEMY_INTERVAL)
    {
        return;
    }
    else
    {
        m_recorder=0;
        for (int i=0;i<ENEMY_NUM;i++)
        {
            //如果是空闲的敌机
            if (m_enemys[i].m_free)
            {
                m_enemys[i].m_free=false;

                //设置坐标
                m_enemys[i].m_X=rand()%(GAME_WIDTH-m_enemys[i].m_Rect.width());
                m_enemys[i].m_Y=-m_enemys[i].m_Rect.height();
                break;
            }
        }
    }
}

void MainScene::collisionDetection()
{
    //遍历所有非空闲敌机
    for (int i=0;i<ENEMY_NUM;i++)
    {
        if (!m_enemys[i].m_free)
        {
            for (int j=0;j<BULLET_NUM;j++)
            {
                if (!m_plane.m_bullets[j].m_free)
                {
                    //如果子弹和飞机相交，发生碰撞，同时将飞机和子弹的空闲状态设置为真
                    if (m_enemys[i].m_Rect.intersects(m_plane.m_bullets[j].m_Rect))
                    {
                        m_enemys[i].m_free=true;
                        m_plane.m_bullets[j].m_free=true;

                        //播放爆炸效果
                        for (int k=0;k<BOMB_NUM;k++)
                        {
                            if (m_bombs[k].m_free)
                            {
                                m_bombs[k].m_free=false;

                                //更新爆炸坐标
                                m_bombs[k].m_X=m_enemys[i].m_X;
                                m_bombs[k].m_Y=m_enemys[i].m_Y;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}


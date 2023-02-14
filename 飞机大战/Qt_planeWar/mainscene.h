#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QWidget>
#include <QTimer>
#include "map.h"
#include "plane.h"
#include "bullet.h"
#include "enemyplane.h"
#include "bomb.h"

class MainScene : public QWidget
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();

    //初始化场景
    void initScene();

    //启动游戏
    void playGame();

    //更新游戏中所有元素的坐标
    void upDatePosition();

    //绘制到屏幕中
    void paintEvent(QPaintEvent*);

    //重写鼠标移动事件
    void mouseMoveEvent(QMouseEvent*);

    //敌机出场
    void enemyToScene();

    //碰撞检测
    void collisionDetection();

    //敌机数组
    EnemyPlane m_enemys[ENEMY_NUM];

    //敌机出场的时间间隔
    int m_recorder=0;

    //地图对象
    Map m_map;

    //飞机对象
    Plane m_plane;

    //定时器
    QTimer m_timer;

    //爆炸数组
    Bomb m_bombs[BOMB_NUM];

    //子弹对象
//    Bullet temp_bullet;
};
#endif // MAINSCENE_H

#ifndef CONFIG_H
#define CONFIG_H

/**********游戏数据配置**********/
#define GAME_WIDTH 480   //宽度
#define GAME_HEIGHT 700   //高度
#define GAME_TITLE "飞机大战 v1.0"   //标题
#define GAME_ICON ":/images/me1.png"   //图标加载路径
#define GAME_RATE 10   //定时器刷新的时间间隔，单位ms

/**********地图数据配置**********/
#define MAP_PATH ":/images/background.png"   //地图加载路径
#define MAP_SCROLL_SPEED 2   //地图滚动速度

/**********飞机数据配置**********/
#define PLANE_PATH ":/images/me1.png"

/**********子弹数据配置**********/
#define BULLET_PATH ":/images/bullet1.png"
#define BULLET_SPEED 5   //子弹移动速度
#define BULLET_NUM 30   //弹匣中子弹个数
#define BULLET_INTERVAL 20   //发射间隔

/**********敌机数据配置**********/
#define ENEMY_PATH ":/images/enemy2.png"
#define ENEMY_SPEED 5
#define ENEMY_NUM 20
#define ENEMY_INTERVAL 30

/**********爆炸数据配置**********/
#define BOMB_PATH ":/images/enemy2_down%1.png"
#define BOMB_MAX 4   //爆炸图片最大索引
#define BOMB_NUM 20
#define BOMB_INTERVAL 10

#endif // CONFIG_H

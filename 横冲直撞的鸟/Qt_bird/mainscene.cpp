#include "mainscene.h"
#include "ui_mainscene.h"
#include <QIcon>
#include <QPainter>
#include <QScreen>

MainScene::MainScene(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    //设置图标
    this->setWindowIcon(QIcon(":/Bird/birdIcon.ico"));

    //创建鸟对象
    this->m_bird=new Bird;

    //将鸟对象显示到窗口中
    this->m_bird->setParent(this);

    //设置窗口尺寸
    this->setFixedSize(this->m_bird->width(),this->m_bird->height());

    //启动鸟飞翔的定时器
    this->m_bird->running();

    //监听鸟切图的信号
    connect(this->m_bird,&Bird::changePix,[=](){
        update();   //手动调用绘图事件
    });

    //监听鸟拖拽移动的信号
    connect(this->m_bird,&Bird::moving,[=](QPoint point){
        this->move(point);

        //鼠标拖拽的时候，更新当前窗口的位置
        m_auto_pos=point;
    });

    //创建定时器对象
    this->timer=new QTimer(this);

    //启动定时器
    this->timer->start(30);

    //获取屏幕宽度和高度
    screen_width = QGuiApplication::primaryScreen()->availableGeometry().width();
    screen_height = QGuiApplication::primaryScreen()->availableGeometry().height();


    //监听定时器
    connect(timer,&QTimer::timeout,[=](){
        //如果鼠标没有按下，才能向前移动
        if (!this->m_bird->mouseDown)
        {
            this->m_auto_pos.setX(this->m_auto_pos.x()+5);
        }

        if (this->m_auto_pos.x()>screen_width)
        {
            this->m_auto_pos.setX(-this->m_bird->width());
        }

        //窗口同步移动
        this->move(this->m_auto_pos);
    });

    //去掉标题栏
    this->setWindowFlags(Qt::FramelessWindowHint);

    //设置透明化 120号属性
    this->setAttribute(Qt::WA_TranslucentBackground);

    //设置窗口顶层
    this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);

    //设置起始Y坐标
    this->m_auto_pos.setY(screen_height*0.5-this->m_bird->height());
}

MainScene::~MainScene()
{
    delete ui;
}

void MainScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.drawPixmap(0,0,this->m_bird->m_bird_pix);
}


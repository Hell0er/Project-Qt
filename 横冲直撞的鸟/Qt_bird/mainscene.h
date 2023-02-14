#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QWidget>
#include "bird.h"
#include <QPaintEvent>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainScene; }
QT_END_NAMESPACE

class MainScene : public QWidget
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();

    //鸟对象指针
    Bird* m_bird;

    //重写绘图时间
    void paintEvent(QPaintEvent*);

    //自动移动的位置
    QPoint  m_auto_pos;

    //自动移动定时器
    QTimer* timer;

    //屏幕宽度和高度
    int screen_width;
    int screen_height;

private:
    Ui::MainScene *ui;
};
#endif // MAINSCENE_H

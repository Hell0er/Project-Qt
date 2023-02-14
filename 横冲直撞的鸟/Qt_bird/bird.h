#ifndef BIRD_H
#define BIRD_H

#include <QWidget>
#include <QPixmap>
#include <QTimer>
#include <QPoint>
#include <QMouseEvent>
#include <QMenu>

class Bird : public QWidget
{
    Q_OBJECT
public:
    explicit Bird(QWidget *parent = nullptr);

    //鸟显示的图片
    QPixmap m_bird_pix;

    //最小值下标
    int min=1;
    //最大值下标
    int max=8;

    //定时器
    QTimer* timer;

    //执行动画
    void running();

    //记录分量坐标
    QPoint m_pos;

    //鼠标按下事件
    void mousePressEvent(QMouseEvent*);

    //鼠标移动事件
    void mouseMoveEvent(QMouseEvent*);

    //鼠标释放事件
    void mouseReleaseEvent(QMouseEvent*);

    //鼠标按下的状态
    bool mouseDown=false;

    //右键菜单，实现退出
    QMenu* m_menu;

signals:
    //自定义信号，表示正在切换图片
    void changePix();

    //自定义信号，表示拖拽后主场景应该移动的位置
    void moving(QPoint point);
};

#endif // BIRD_H

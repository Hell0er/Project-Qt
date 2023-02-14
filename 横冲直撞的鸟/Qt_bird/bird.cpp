#include "bird.h"

Bird::Bird(QWidget *parent) : QWidget(parent)
{
    //加载鸟的所有图片资源
    for (int i=0;i<this->max;i++)
    {
        QString str=QString(":/Bird/bird%1").arg(i+1);
        this->m_bird_pix.load(str);
    }

    //设置鸟的尺寸
    this->setFixedSize(this->m_bird_pix.width(),this->m_bird_pix.height());

    //创建定时器对象
    this->timer=new QTimer(this);

    //监听定时器的信号
    connect(timer,&QTimer::timeout,[=](){
        QString str=QString(":/Bird/bird%1").arg(this->min++);
        this->m_bird_pix.load(str);
        if (this->min>this->max)
        {
            this->min=1;
        }

        //抛出自定义信号
        emit changePix();
    });

    //菜单创建
    this->m_menu=new QMenu();

    //连接菜单中退出选项的信号槽
    connect(this->m_menu->addAction("退出"),&QAction::triggered,[=](){
        exit(0);
    });
}

void Bird::running()
{
    //启动定时器
    this->timer->start(100);
}

void Bird::mousePressEvent(QMouseEvent *e)
{
    //鼠标按下时记录分量
    //((QWidget*)this->parent())->frameGeometry().topLeft() 获取当前窗口左上角坐标
    this->m_pos=e->globalPos()-((QWidget*)this->parent())->frameGeometry().topLeft();

    //鼠标按下的状态为真
    this->mouseDown=true;

    //如果是鼠标右键，弹出菜单
    if (e->button()==Qt::RightButton)
    {
        //弹出菜单，位置为鼠标位置
        this->m_menu->popup(QCursor::pos());
    }

    //如果隐藏了“退出”菜单，鸟应该继续飞
    connect(this->m_menu,&QMenu::aboutToHide,[=](){
        this->mouseDown=false;
    });
}

void Bird::mouseMoveEvent(QMouseEvent *e)
{
    //在移动过程中，反向获取到窗口最终移动的位置
    emit this->moving(e->globalPos()-this->m_pos);
}

void Bird::mouseReleaseEvent(QMouseEvent *)
{
    //鼠标释放时，鼠标按下的状态为假
    this->mouseDown=false;
}

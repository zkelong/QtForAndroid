#include "widget.h"

#include <QTimerEvent>
#include <QDateTime>
#include <QTimer>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    //不限次数，一直循环--1
    /*m_timeLabel = new QLabel(this); //实例化
    startTimer(1000);*/

    //获取timerId--2
    /*m_timeLabel = new QLabel(this);
    m_timerId = startTimer(1000);*/

    //使用QTimer--3
    /*m_timeLabel = new QLabel(this);
    QTimer *timer = new QTimer(this);
    timer->setInterval(1000);
    //设置一次性
    timer->setSingleShot(true);
    timer->start();
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimerout()));*/

    //使用一次性QTimer的方法--4
    m_timeLabel = new QLabel(this);
    QTimer::singleShot(1000, this, SLOT(onTimerout()));
}

Widget::~Widget()
{

}

void Widget::onTimerout()
{
    QDateTime current = QDateTime::currentDateTime();
    QString strTime = current.toString("hh:mm:ss");
    m_timeLabel->setText(strTime);
    m_timeLabel->adjustSize();
}

void Widget::timerEvent(QTimerEvent *e)
{
    //只有一个timer,没有使用到timerId--1
    /*QDateTime current = QDateTime::currentDateTime();
    QString strTime = current.toString("hh:mm:ss");
    m_timeLabel->setText(strTime);
    m_timeLabel->adjustSize();
    e->accept();
    QWidget::timerEvent(e);*/

    //获取定时器id,并运行一次后就关掉timer--2
    if(m_timerId == e->timerId()) {
        QDateTime current = QDateTime::currentDateTime();
        QString strTime = current.toString("hh:mm:ss");
        m_timeLabel->setText(strTime);
        m_timeLabel->adjustSize();
        e->accept();
        killTimer(m_timerId);   //执行一次就关掉
        m_timerId = 0;
    }
    QWidget::timerEvent(e);

}

//支持周期性的，一次性的。

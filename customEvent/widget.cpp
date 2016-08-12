#include "widget.h"
#include <QEvent>
#include <QTimer>
#include <QDateTime>
#include <QCoreApplication>
#include <QThread>

class SimpleThread : public QThread
{
public:
    QObject * m_receiver;

    SimpleThread(QObject *receiver)
        :m_receiver(receiver)
    {}

    void run()  //重写run方法
    {
        while(1)
        {
            QThread::msleep(1000);
            CustomEvent *ce = new CustomEvent(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
            QCoreApplication::postEvent(m_receiver, ce);
        }
    }
};

Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
    m_label = new QLabel(this);
    /*--定时器的
    QTimer *timer = new QTimer(this);
    timer->setInterval(1000);
    timer->start();
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    */
    //启动线程
    SimpleThread *t = new SimpleThread(this);
    t->start();
}

Widget::~Widget()
{
}

bool Widget::event(QEvent *e)
{
    if(e->type() == CustomEvent::evType())
    {
        CustomEvent *ce = (CustomEvent*)e;
        m_label->setText(ce->m_msg);
        m_label->adjustSize();
        e->accept();
        return true;    //我们处理了
    }
    return QWidget::event(e);
}

void Widget::onTimeout()
{
    CustomEvent *ce = new CustomEvent(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    QCoreApplication::postEvent(this, ce);
}

#include "widget.h"
#include <QResizeEvent>
#include <QKeyEvent>
#include <QMouseEvent>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    m_label = new QLabel("Hello World", this);
    m_label->setGeometry(10, 10, 300, 50);  //绝对坐标布局
}

Widget::~Widget()
{

}

void Widget::resizeEvent(QResizeEvent *e)
{
    /*
    QSize size = e->size();
    QSize labelSize = m_label->size();
    m_label->move((size.width() - labelSize.width())/2,
                  (size.height() - labelSize.height())/2);
    QWidget::resizeEvent(e);   //也要返回给基类处理
    */
}

void Widget::keyPressEvent(QKeyEvent *e)
{
    switch (e->key()) {
    case Qt::Key_Left:
        m_label->move(m_label->x() - 10, m_label->y());
        break;
    case Qt::Key_Right:
        m_label->move(m_label->x() + 10, m_label->y());
        break;
    case Qt::Key_Up:
        m_label->move(m_label->x(), m_label->y() - 10);
        break;
    case Qt::Key_Down:
        m_label->move(m_label->x(), m_label->y() + 10);
        break;
    default:
        QWidget::keyPressEvent(e);   //其他的要返回给基类处理
        break;
    }
    e->accept();
}

void Widget::mousePressEvent(QMouseEvent *e)
{
    m_label->move(e->pos());
    QWidget::mousePressEvent(e);
}


/*
鼠标事件：
mousePressEvent()
mouseReleaseEvent()
MouseMoveEnvent()
....
*/


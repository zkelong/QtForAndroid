#include "mybutton.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

MyButton::MyButton(QWidget *parent)
    : QWidget(parent)
    , m_text("Button")
    , m_pressed(false)
    , m_frame(false)
{}

MyButton::~MyButton()
{}

void MyButton::setText(const QString &text)
{
    m_text = text;
    update();
}

void MyButton::mousePressEvent(QMouseEvent *e)
{
    if(!m_pressed)
    {
        m_pressed = true;
        update();
    }
}

void MyButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(m_pressed)
    {
        m_pressed = false;
        update();
        emit clicked();
    }
}

void MyButton::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    if(m_pressed)
    {
        p.fillRect(rect(), Qt::lightGray);
    }
    else
    {
        p.fillRect(rect(), Qt::gray);
    }
    p.setPen(Qt::blue);
    p.setBrush(Qt::NoBrush);
    if(m_frame)
    {
        p.drawRect(0, 0, width() - 1, height() - 1);
    }
    p.drawText(rect(), Qt::AlignCenter, m_text);
}

void MyButton::enterEvent(QEvent *e)
{
    if(!m_frame)
    {
        m_frame = true;
        update();
    }
    qDebug() << "m_frame...." << m_frame;
}

void MyButton::leaveEvent(QEvent *e)
{
    if(m_frame)
    {
        m_frame = false;
        update();
    }
}

#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    ,m_shapeType(point)
    ,m_shape(createShape(point))
{
}

Widget::~Widget()
{

}

void Widget::onShapeChanged(int shapeType)
{
    m_shapeType = shapeType;
    if(m_shape->isEmpty()) delete m_shape;
    else m_shape->append(m_shape);
    m_shape = createShape(shapeType);
}

void Widget::clear()
{
   deleteAllShapes();
   m_shape = createShape(m_shapeType);
   update();
}

void Widget::undo()
{
    bool needUpdate = false;
    if(!m_shape->isEmpty())
    {
        needUpdate = true;
        delete m_shape;
        m_shape = createShape(m_shapeType);
    }
    else
    {
        needUpdate = true;
        delete m_shapes.takeLast();
    }
    if(needUpdate)
    {
        update();
    }
}

void Widget::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.fillRect(rect(), Qt::black);
    QPen pen(Qt::white);
    pen.setWidth(2);
    p.setPen(pen);

    int size = m_shapes.size();
    for(int i = 0; i < size; i++)
    {
        m_shapes.at(i)->paint(&p);
    }
    if(m_shape && !m_shape->isEmpty())
    {
        m_shape->paint(&p);
    }
}

void Widget::mousePressEvent(QMouseEvent *e)
{
    if(m_shape->mousePress(e))
    {
        update();
    }
}

void Widget::mouseMoveEvent(QMouseEvent *e)
{
    if(m_shape->mouseRelease(e))
    {
        m_shapes.append(m_shape);
        m_shape = createShape(m_shapeType);
        update();
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *e)
{
    if(m_shape->mouseRelease(e))
    {
        m_shapes.append(m_shape);
        m_shape = createShape(m_shapeType);
        update();
    }
}

void Widget::deleteAllShapes()
{
    if(m_shape)
    {
        delete m_shape;
        m_shape = 0;
    }

    int size = m_shapes.size();
    if(size)
    {
        for(int i = 0; i < size; i++)
        {
            delete m_shapes.at(i);
        }
        m_shapes->clear();
    }
}

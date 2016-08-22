#include "shapeselector.h"
#include <QPainter>
#include <QMouseEvent>

ShapeSelector::ShapeSelector()
{
    m_shapeRects = new QRect();
    m_shapePixmaps = new QPixmap[shapes];
    m_shapePixmaps[point].load(":/point.png");
    m_shapePixmaps[line].load(":/line.png");
    m_shapePixmaps[rectangle].load(":/rectangle.png");
    m_shapePixmaps[roundRectangle].load(":/roundRectangle.png");
    m_shapePixmaps[ellipse].load(":/ellipse.png");
    m_shapePixmaps[path].load(":/path.png");
}

ShapeSelector::~ShapeSelector()
{
    delete [] m_shapePixmaps;
    delete [] m_shapeRects;
}

void ShapeSelector::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    p.setPen(Qt::lightGray);
    p.setBrush(Qt::white);
    p.drawRect(rect());
    for(int i = 0; i < shapes; i++)
    {
        if(m_currentShape == i)
        {
            p.fillRect(m_shapeRects[i], Qt::blue);
        }
        p.drawPixmap(m_shapeRects[i], m_shapePixmaps[i]);
    }
}

void ShapeSelector::mousePressEvent(QMouseEvent *e)
{
    QPoint pt = e->pos();
    for(int i = 0; i < shapes; i++)
    {
        if(m_shapeRects[i].contains(pt))
        {
            if(m_currentShape != i)
            {
                m_currentShape = i;
                update();
                emit shapeChanged(i);
            }
            break;
        }
    }
}

void ShapeSelector::resizeEvent(QResizeEvent *e)
{
    QSize sz = e->size();
    int y = (sz.height() - m_shapePixmaps[point].height());
    for(int i = 0, x = 4; i < shapes; i++)
    {
        m_shapeRects[i].setRect(x, y, m_shapePixmaps[i].width()
                                ,m_shapePixmaps[i].height());
        x += 4 + m_shapePixmaps[i].width();
    }
    QWidget::resizeEvent(e);
}

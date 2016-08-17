#ifndef SHAPESELECTOR_H
#define SHAPESELECTOR_H

#include <QWidget>
#include <QRect>
#include <QPixmap>
#include <QSize>
#include "shapetype.h"

class ShapeSelector: public QWidget
{
    Q_OBJECT
public:
    ShapeSelector(QWidget *parent = 0);
    ~ShapeSelector(){}

    QSize sizeHint() const {return QSize(40*shapes, 40);}

signals:
    void shapeChanged(int shape);

protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void resizeEvent(QResizeEvent *e);

protected:
    QRect *m_shapeRects;
    QPixmap *m_shapePixmaps;
    int m_currentShape;
};

#endif // SHAPESELECTOR_H

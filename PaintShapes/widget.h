#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "shapefactory.h"
#include <QVector>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

    QSize sizeHint() const {return QSize(300, 300);}

protected slots:
    void onShapeChanged(int shapeType);
    void clear();
    void undo();

protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void deleteAllShapes();

protected:
    int m_shapeType;
    Shape *m_shape;
    QVector<Shape*> m_shapes;
};

#endif // WIDGET_H

#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H
#include <QPainter>
#include <QMouseEvent>

class Shape
{
public:
    Shape(int shapeType)
        :m_shapeType(shapeType)
    {}
    virtual ~Shape(){}
    int shapeType() {return m_shapeType;}
    virtual bool isEmpty() {return false;}
    virtual bool paint(QPainter *p) = 0;
    virtual bool mousePress(QMouseEvent *e) = 0;
    virtual bool MouseMove(QMouseEvent *e) = 0;
    virtual bool mouseRelease(QMouseEvent *e) = 0;

    int m_shapeType;
};

Shape *createShape(int type);

#endif // SHAPEFACTORY_H

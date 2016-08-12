#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class Widget : public QWidget   //共有继承
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
};

#endif // WIDGET_H

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

protected:
    void resizeEvent(QResizeEvent *e);  //重写对应的虚函数
    void keyPressEvent(QKeyEvent *e);
    //void keyReleaseEvent(QKeyEvent *e);
    void mousePressEvent(QMouseEvent *e);

protected:
    QLabel *m_label;
};

#endif // WIDGET_H

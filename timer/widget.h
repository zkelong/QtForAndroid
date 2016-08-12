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

protected slots:
    void onTimerout();

protected:
    void timerEvent(QTimerEvent *e); //Qt预定义方法
private:
    QLabel *m_timeLabel;
    int m_timerId;  //获取timerId
};

#endif // WIDGET_H

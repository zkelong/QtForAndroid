#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QEvent>
#include <QImage>
#include <QTimer>

class ImageEvent : public QEvent
{
public:
    ImageEvent();
    ~ImageEvent();

    static QEvent::Type m_evType;
    QImage m_image;
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

    bool event(QEvent *e);

    QSize sizeHint() const {return QSize(480, 480);}

protected slots:
    void onTimerout();

protected:
    void paintEvent(QPaintEvent *e);

protected:
    QImage m_image;
};



#endif // WIDGET_H

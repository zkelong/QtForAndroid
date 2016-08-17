#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPixmap>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

protected slots:
    void mouseDoubleClickEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);

protected:
    QString m_filePath;
    QPixmap m_pixmap;
};

#endif // WIDGET_H

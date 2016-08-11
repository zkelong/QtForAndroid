#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include "customevent.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    bool event(QEvent *e);

protected slots:
    void onTimeout();

protected:
    QLabel *m_label;
};

#endif // WIDGET_H

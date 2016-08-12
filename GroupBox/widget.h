#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QGroupBox>
#include <QRadioButton>
#include <QCheckBox>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

protected slots:
    void onToggled();
    void onCheckState(int state);

protected:
    QLabel *m_stateLabel;
};

#endif // WIDGET_H

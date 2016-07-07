#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void onLaunch();
    void onGetActivityInfo();
    void onCapture();

private:
    QLineEdit *m_actionEdit;    //用于输入 action
    QLabel*m_activityInfo;  //是显示 Activity 类名等信息的
    QLabel *m_capturedImage;    //用来显示捕捉到的照片
};

#endif // WIDGET_H

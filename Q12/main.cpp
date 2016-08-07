#include "Q12Widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}

/*
signal == public 定义信号
emit 发射信号

从QObject(或其派生类)继承
Q_OBJECT
signals //只需要声明，不需要实现，连接到信号
声明信号
链接一个槽到自定义信号
emit你的信号

使用自定义信号
1.继承QObject
2.Q_Objec
3.sinals;
4.signals后声明信号
5.定义响应的槽
6.链接信号--emit信号或链接其他信号
**/

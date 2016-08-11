#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])    //Qt程序入口
{
    QApplication a(argc, argv); //全局唯一
    Widget w;   //创建对象
    w.show();   //显示

    return a.exec();    //事件循环，监听用户操作
}

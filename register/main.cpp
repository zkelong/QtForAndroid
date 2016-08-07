#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    a.installEventFilter(&w);
    w.setMinimumSize(480, 360);
    w.show();

    return a.exec();
}

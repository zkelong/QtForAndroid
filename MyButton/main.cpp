#include "widget.h"
#include "mybutton.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    MyButton btn(&w);
    btn.setText("Quit");
    QObject::connect(&btn, SIGNAL(clicked()),
                     &a, SLOT(quit()));
    w.show();

    return a.exec();
}

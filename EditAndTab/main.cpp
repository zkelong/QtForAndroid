#include "widget.h"
#include <QApplication>
#include <QTextEdit>
#include <QTabWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTabWidget *tab = new QTabWidget;
    QTextEdit *edit = new QTextEdit;
    Widget *w = new Widget;

    tab->addTab(w, "edit");
    tab->addTab(edit, "recv");

    QObject::connect(w, SIGNAL(message(QString)), edit, SLOT(append(QString)));
    edit->append("plain text");
    tab->show();
//    Widget w;
//    w.show();

    return a.exec();
}

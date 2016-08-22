#include "widget.h"
#include "shapeselector.h"
#include <QObject>
#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QPushButton>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget w;
    Widget *paintWidget = new Widget;
    paintWidget->setMinimumSize(paintWidget->sizeHint());

    QVBoxLayout *layout = new QVBoxLayout(&w);

    QHBoxLayout *actionLayout = new QHBoxLayout;
    layout->addLayout(actionLayout);
    layout->addSpacing(2);

    ShapeSelector *selector = new ShapeSelector;
    selector->setMinimumSize(selector->sizeHint());
    actionLayout->addWidget(selector);

    QSize iconSize(48, 48);
    QPushButton *btn = new QPushButton();
    btn->setToolTip("undo");
    btn->setIcon(QIcon("undo.png"));
    btn->setIconSize(iconSize);
    QObject::connect(btn, SIGNAL(clicked()),
                     paintWidget, SLOT(undo()));
    actionLayout->addWidget(btn);

    btn = new QPushButton();
    btn->setToolTip("erase all");
    btn->setIcon(QIcon("undo.png"));
    btn->setIconSize(iconSize);
    QObject::connect(btn, SIGNAL(clicked()),
                     paintWidget, SLOT(undo()));
    actionLayout->addWidget(btn);

    actionLayout->addStretch(1);

    QObject::connect(selector, SIGNAL(shapeChanged(int)),
                     paintWidget, SLOT(onShapeChanged(int)));

    w.show();

    return a.exec();
}

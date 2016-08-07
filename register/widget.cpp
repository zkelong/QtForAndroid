#include "widget.h"
#include "register.h"
#include <QPushbutton>
#include <QEvent>
#include <QKeyEvent>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QPushButton *button = new QPushButton("注册", this);
    connect(button, SIGNAL(clicked()), this, SLOT(onRegisterButton()));
}

Widget::~Widget()
{

}

bool Widget::eventFilter(QObject *watched, QEvent *e)
{
    if(e->type() == QEvent::KeyPress)
    {
        if(((QKeyEvent*)e)->key() == Qt::Key_Home)
        {

            for(int i = 0; i < m_subWidgets.size(); i++)
            {
                m_subWidgets.at(i)->deleteLater();
            }
            m_subWidgets.clear();
            e->accept();
            return true;
        }
    }
    return QWidget::eventFilter(watched, e);
}

void Widget::onRegisterButton()
{
    Register *reg = new Register(this);
    reg->setAutoFillBackground(true);
    reg->setGeometry(rect());
    m_subWidgets.push_front(reg);
    reg->show();
}

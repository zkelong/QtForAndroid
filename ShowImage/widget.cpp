#include "widget.h"
#include <QPainter>
#include <QPen>
#include <QFileDialog>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
}

Widget::~Widget()
{

}

void Widget::mouseDoubleClickEvent(QMouseEvent *e)
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"),
                             QDir::currentPath(),
                             tr("Images (*.png *.gif *.bmp *.xpm *jpg)"));
    if(!fileName.isEmpty())
    {
        m_pixmap.load(fileName);\
        m_filePath = fileName;
    }
}

void Widget::paintEvent(QPaintEvent *e)
{
    QPainter p(this);//Qwidget,QImage...可以用来画画
    //比drawImage快些
    //p.drawPixmap(0, 0, m_pixmap); //指定画布起始位置
    p.drawPixmap(rect(), m_pixmap); //根据矩形进行缩放
    QPen pen(Qt::blue);
    p.setPen(pen);
    p.drawText(10, 30, m_filePath);
}

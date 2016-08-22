#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QWidget>

class MyButton: public QWidget
{
    Q_OBJECT
public:
    MyButton(QWidget *parent = 0);
    ~MyButton();

    QSize sizeHint() const {return QSize(70, 30);}
    void setText(const QString &text);
    QString text() {return m_text;}

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);

protected:
    QString m_text;
    bool m_pressed;
    bool m_frame;
};

#endif // MYBUTTON_H

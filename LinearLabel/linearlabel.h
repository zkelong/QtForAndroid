#ifndef LINEARLABEL_H
#define LINEARLABEL_H
#include <QWidget>
#include <QColor>
#include <QPixmap>
#include <QLinearGradient>
#include <QSize>

class LinearLabel : public QWidget
{
    Q_OBJECT
public:
    LinearLabel(const QString &text, QWidget *parent = 0);
    ~LinearLabel();

    void setBackgroundColor(const QColor & color) //设置背景颜色
    {
        m_backgroundColor = color;
    }
    void setBackgroundImage(const QPixmap &pixmap)  //设置背景图片
    {
        m_backgroundPixmap = pixmap;
    }
    void setTextColor(const QColor &color)  //设置文本颜色
    {
        m_textColor = color;
    }

    void setColorAt(qreal position, const QColor & color);  //渐变颜色
    void clearGradient();  //清除渐变

    void setAlignment(Qt::AlignmentFlag flag)  //设置对齐方式
    {
        m_flags = flag;
    }

    void setPenWidth(qreal width)  //画笔粗细
    {
        m_penWidth = width;
    }

    QSize sizeHint() const;

public slots:
    void setText(const QString &text)
    {
        m_text = text;
        update();
    }

protected:
    void paintEvent(QPaintEvent *e);

private:
    QString m_text;
    QColor m_backgroundColor;
    QPixmap m_backgroundPixmap;
    QColor m_textColor;
    QLinearGradient *m_linearGradient;
    int m_flags;
    qreal m_penWidth;
};

#endif // LINEARLABEL_H


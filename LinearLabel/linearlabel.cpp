#include "linearlabel.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QFontMetrics>
#include <QRectF>

LinearLabel::LinearLabel(const QString &text, QWidget *parent)
    : QWidget(parent)
    , m_text(text)
    , m_backgroundColor(Qt::transparent)
    , m_textColor(Qt::black)
    , m_linearGradient(0)
    , m_flags(Qt::AlignLeft | Qt::AlignVCenter)
    , m_penWidth(1)
{
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    //设置尺寸策略：水平方向策略Preferred，允许布局管理器根据情况设置LinearLabel的宽度
    //垂直方向策略为Fixed，布局管理器会保存sizeHint()返回的高度不变。
}

LinearLabel::~LinearLabel()
{
    if(m_linearGradient) delete m_linearGradient;
}

//调用该方法时，会动态生成一个QLinearGradient对象保存渐变设置。
//QLinearGradient是线性渐变类起始(setStart()), 结尾(setFinalStop()), 关键节点(setColorAt())
//先创建一个支持渐变的QBrush对象，然后使用此对象创建一个画笔（QPen对象），再把画笔给画师QPainter，画师绘制文本时就可以用渐变效果了
void LinearLabel::setColorAt(qreal position, const QColor &color)
{
    if(!m_linearGradient)
    {
        m_linearGradient = new QLinearGradient();
    }
    m_linearGradient->setColorAt(position, color);
}

void LinearLabel::clearGradient()
{
    if(m_linearGradient)
    {
        delete m_linearGradient;
        m_linearGradient = 0;
        update();
    }
}

QSize LinearLabel::sizeHint() const   //设置字体
{
    if(m_text.isEmpty()) return QSize();
    QFontMetrics fm = fontMetrics();
    return QSize( fm.width(m_text) + 8, fm.height() + 4 );
}

void LinearLabel::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QRect r = rect();
    if(m_backgroundPixmap.isNull())
    {
        painter.fillRect(r, m_backgroundColor);
    }
    else
    {
        painter.drawPixmap(r, m_backgroundPixmap);
    }

    QFontMetrics fm = painter.fontMetrics();
    QString elidedText = fm.elidedText(m_text, Qt::ElideRight
                                       , r.width() - 4
                                       );
    if(m_linearGradient)
    {
        QRectF boundingRect = fm.boundingRect(r, m_flags,elidedText);
        m_linearGradient->setStart(boundingRect.topLeft());
        m_linearGradient->setFinalStop(boundingRect.bottomLeft());
        QPen linearPen(QBrush(*m_linearGradient), m_penWidth);
        painter.setPen(linearPen);
        painter.drawText(boundingRect, m_flags, elidedText);
    }
    else
    {
        QPen pen(m_textColor, m_penWidth);
        painter.setPen(pen);
        painter.drawText(r, m_flags, elidedText);
    }
}


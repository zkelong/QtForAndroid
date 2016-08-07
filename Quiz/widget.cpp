#include "widget.h"
#include <QVBoxLayout>

static const char *g_question[] = {
    "“床前明月光”中的床是什么？"
    ,"C语言之父"
    ,"学到了多少"
};

static const char *g_answers[] = {
    "井台上的围栏，即井床"
    ,"Dennis Ritchie"
    ,"好多！"
};


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);    //parent, this 使用该布局管理器
    layout->addStretch(1);
    m_label = new QLabel(QString::fromUtf8(g_question[0]));
    layout->addWidget(m_label, 0, Qt::AlignCenter);
    layout->addSpacing(10); //间隔
    QHBoxLayout *actionLayout = new QHBoxLayout;
    layout->addLayout(actionLayout);    //布局嵌套
    actionLayout->addStretch(1);    //可伸缩系数
    m_questionButton = new QPushButton("Question");
    QObject::connect(m_questionButton, SIGNAL(clicked()),
                     this, SLOT(onQuestionClicked()));
    actionLayout->addWidget(m_questionButton);
    m_answerButton = new QPushButton("Answer");
    actionLayout->addWidget(m_answerButton);
    QObject::connect(m_answerButton, SIGNAL(clicked()),
                     this, SLOT(onAnswerClicked()));
    actionLayout->addStretch(1);    //可伸缩系数，中间的剧中显示
}

Widget::~Widget()
{

}

void Widget::onQuestionClicked()
{
    int count = sizeof(g_question) / sizeof(g_question[0]);
    m_questionIndex = (m_questionIndex + 1) % count;
    m_label->setText(QString::fromUtf8(g_question[m_questionIndex]));
}

void Widget::onAnswerClicked()
{
    m_label->setText((QString::fromUtf8(g_answers[m_questionIndex])));
}

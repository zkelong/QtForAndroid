#include "Q12Widget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QApplication>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
}

Widget::~Widget()
{
    delete [] m_scores;
}

void Widget::setupUI()
{
    const char* questions[] = {
        "1. 我知道对我的工作要求吗？",
        "2. 我有做好我的工作所需要的\n材料和设备吗？",
        "3. 在工作中，我每天都有机会\n做我最擅长做的事吗？",
        "4. 在过去的七天里，我因工作\n出色而受到表扬吗？",
        "5. 我觉得我的主管或同事关心\n我的个人情况吗？",
        "6. 工作单位有人鼓励我的发展吗？",
        "7. 在工作中，我觉得我的意见受\n到重视吗？",
        "8. 公司的使命目标使我觉得我的\n工作重要吗？",
        "9. 我的同事们致力于高质量的工作吗？",
        "10. 我在工作单位有一个最要好的\n朋友吗？",
        "11. 在过去的六个月内，工作单位\n有人和我谈及我的进步吗？",
        "12. 过去一年里，我在工作中有机会\n学习和成长吗？"
    };
    m_nQuestionCount = sizeof(questions)/sizeof(questions[0]);
    m_scores = new QComboBox*[m_nQuestionCount];

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *line;
    QLabel * question;
    QComboBox *score;
    QStringList scoreList("0");
    scoreList << "1" << "2" << "3" << "4" << "5";

    for(int i = 0; i < m_nQuestionCount; i++)
    {
        line = new QHBoxLayout();
        question = new QLabel(questions[i], this);
        //向line布局对象（QHBoxLayout）中添加一个标签控件question（QLabel实例），同时指定它的stretch为4，水平靠左垂直居中对齐。
        //stretch，alignment有默认值。stretch是个系数，界面尺寸变化调整它所管理的元素时用于计算该给那个元素多少空间。布局会参考各个元素的stretch所谓权重
        line->addWidget(question, 4, Qt::AlignLeft | Qt::AlignVCenter);
        score = new QComboBox(this);
        score->addItems(scoreList);
        score->setCurrentIndex(3);
        line->addWidget(score, 1, Qt::AlignRight | Qt::AlignVCenter);
        m_scores[i] = score;

        mainLayout->addLayout(line);  //使用默认值0
    }

    QPushButton * submit = new QPushButton("提交", this);
    //没有用QObject::connect()函数链接信号和槽，因为Widget隔代继承QObject
    //QObject有静态和动态的connect()函数
    //下面SIGNAL(clicked())--"2clicked";SLOT(onCancelButton())--"2onSubmit"
    connect(submit, SIGNAL(clicked()), this, SLOT(onSubmit()));
    QPushButton * cancel = new QPushButton("取消", this);
    //qApp就是Qt框架实现的QApplication类的实例，本质是一个宏。
    //connect(cancel, SIGNAL(clicked()), qApp, SLOT(quit()));
    //connect(cancel, SIGNAL(clicked()), this, SIGNAL(cancel())); //信号可以链接信号
    connect(cancel, SIGNAL(clicked()), this, SLOT(onCancelButton())); //链接自己的槽
    //layout->setR
    line = new QHBoxLayout();
    line->addStretch(1);
    line->addWidget(cancel, 0, Qt::AlignRight | Qt::AlignVCenter);
    line->addWidget(submit, 0, Qt::AlignRight | Qt::AlignVCenter);

    mainLayout->addLayout(line);

    connect(this, SIGNAL(cancel()), this, SLOT(onCnacel()));
}

void Widget::onSubmit(){
    QString content;
    for(int i = 0; i < m_nQuestionCount; i++)
    {
        content += QString("问题%1: %2分\n").arg(i+1).arg(m_scores[i]->currentText());
    }

    QMessageBox * msg = new QMessageBox(QMessageBox::Information, "测评结果", content, QMessageBox::Ok, this);
    msg->exec();
}

void Widget::onCnacel()
{
    //question静态方法，param: this, 标题，显示信息
    QMessageBox::StandardButton ret = QMessageBox::question(this, "问题"
                          ,"真的要退出测评？"
                          ,QMessageBox::Yes | QMessageBox::No);
    if(ret == QMessageBox::Yes) {
        qApp->quit();
    }
}

void Widget::onCancelButton()
{
    emit cancel();  //qt的关键字，不是c++的，emit是个空宏
}

/*
MessageBox静态方法
about..
information...
warning..
question..
critical..
new QMessageBox
exec()/show()

ComboBox组合框方法
addItem(QString,...)
addItem(QIcon, QString,...)
additems(QStringList,...)
InsertItem(int,...)
setItemText(...)/itemText   //设置/取
setItemIcon(...)/itemIcom
setItemData(...)/itemData

QGridLayout表格布局方法
addWidget(widget, row, col, ...)
addLayout(layout, row, col, ...)
...
可以合并列

使用槽
从QOject(或其派生类)集成
Q_OBJECT
slot
成员函数
*/


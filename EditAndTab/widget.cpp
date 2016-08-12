#include "widget.h"
#include <QVBoxLayout>
#include <QGroupBox>
#include <QTextEdit>
#include <QPushButton>
#include <QDebug>

#define STYLE_BOLD_TEXT_MARKER \
    "<font color=\"%1\"><b>%2</b></font>"
#define STYLE_TEXT_MARKER \
    "<font color=\"%1\">%2</font>"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    ,m_checkedColor(0)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    QGroupBox *group = new QGroupBox;
    layout->addWidget(group);
    group->setTitle("Text Color");

    QVBoxLayout *colorLyout = new QVBoxLayout(group);
    QRadioButton *btn = new QRadioButton("red");
    btn->setStyleSheet("*{color: red}");
    btn->setChecked(true);
    m_checkedColor = btn;
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(onClorClicked(bool)));
    colorLyout->addWidget(btn);

    btn = new QRadioButton("blue");
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(onClorClicked(bool)));
    btn->setStyleSheet("*{color: blue}");
    colorLyout->addWidget(btn);

    btn = new QRadioButton("green");
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(onClorClicked(bool)));
    btn->setStyleSheet("*{color: green}");
    colorLyout->addWidget(btn);

    btn = new QRadioButton("brown");
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(onClorClicked(bool)));
    btn->setStyleSheet("*{color: brown}");
    colorLyout->addWidget(btn);

    m_boldOption = new QCheckBox("BOLD");
    layout->addWidget(m_boldOption);

    m_lineEdit = new QLineEdit;
    layout->addWidget(m_lineEdit);

    QPushButton *submit = new QPushButton("Submit");
    connect(submit, SIGNAL(clicked(bool)), this, SLOT(onSubmit()));
    layout->addWidget(submit);

    layout->stretch(1);
}

Widget::~Widget()
{

}

void Widget::onClorClicked(bool checked)
{
    if(checked)
    {
        m_checkedColor = qobject_cast<QRadioButton*>(sender());
        qDebug() << m_checkedColor->text();
    }

}

void Widget::onSubmit()
{
    QString text = m_lineEdit->text();
    if(m_boldOption->isChecked())
    {
        QString str = QString(STYLE_BOLD_TEXT_MARKER)
                .arg(m_checkedColor->text())
                .arg(text);
        emit message(str);
    }
    else
    {
        QString str = QString(STYLE_TEXT_MARKER)
                .arg(m_checkedColor->text())
                .arg(text);
        emit message(str);
    }
    m_lineEdit->clear();
}

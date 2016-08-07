#ifndef Q12WIDGET_H
#define Q12WIDGET_H

#include <QWidget>
#include <QComboBox>

class Widget : public QWidget
{
    Q_OBJECT  //想定义自己的信号与槽必须提供的通行证

public:
    Widget(QWidget *parent = 0);
    ~Widget();

protected:
    void setupUI();

protected slots:  //定义槽，可以用private，public，protected修饰
    void onSubmit(); //槽就是一个函数，定义了它就必须在源文件中实现，否则链接器报无法找到
    void onCnacel();    //实现一个槽
    void onCancelButton();

signals:    //是个宏，就是public 标记符
    void cancel();  //像成员函数，没有任何区别

private:
    QComboBox ** m_scores;
    int m_nQuestionCount;
};

#endif // Q12WIDGET_H

/*
Q12没有使用QWidget::setLayout()，因为QLayout(QWidget *parent),指定parent后，
    这个布局就会作为parent这个widget的顶层布局，无需要再调用setLayout()，而QWidget::layout()也会返回你创建的那个layout。
    一旦为QWidget设置了布局，布局就会负责接管下列任务：
        a.把子widget们安排到合适的位置
        b.自动计算窗口的默认尺寸
        c.自动计算窗口的最小尺寸
        d.尺寸变化处理
    当widget的内容变化时自动更新调整整个UI布局，下面变化会引起布局调整：
        a.字体、文本以及其他内容
        b.隐藏或显示一个子widget
        c.移除某些子widgets
*/

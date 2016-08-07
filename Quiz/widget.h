#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

protected slots:
    void onQuestionClicked();
    void onAnswerClicked();

private:
    QLabel *m_label;
    QPushButton *m_questionButton;
    QPushButton *m_answerButton;
    int m_questionIndex;
};

#endif // WIDGET_H

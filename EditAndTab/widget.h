#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QRadioButton>
#include <QCheckBox>
#include <QLineEdit>
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

signals:
    void message(const QString &msg);

protected slots:
    void onClorClicked(bool checked);
    void onSubmit();

protected:
    QRadioButton *m_checkedColor;
    QCheckBox *m_boldOption;
    QLineEdit *m_lineEdit;
};

#endif // WIDGET_H

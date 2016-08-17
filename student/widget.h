#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QTableWidgetItem>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

protected slots:
    void onItemChanged(QTableWidgetItem *item);
    void onCurrentIndexChanged(int index);

protected:
    QTableWidget *m_table;
};

#endif // WIDGET_H

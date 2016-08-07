#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

class Register : public QWidget
{
    Q_OBJECT
public:
    Register(QWidget *parent = 0);
    ~Register();

protected slots:
    void onConfiremButton();
    void onCancelButton();

public:
    bool eventFilter(QObject *watched, QEvent *e);

protected:
    QLineEdit *m_nameEdit;
    QLineEdit *m_passwordEdit;
    QPushButton *m_confirmButton;
    QPushButton *m_cancelButton;

};

#endif // REGISTER_H

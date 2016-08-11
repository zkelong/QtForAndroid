#ifndef CUSTOMEVENT_H
#define CUSTOMEVENT_H

#include <QEvent>
#include <QString>

class CustomEvent : public QEvent
{
public:
    CustomEvent(const QString & msg);

    static QEvent::Type evType();

    static QEvent::Type m_eventType;
    QString m_msg;
};

#endif // CUSTOMEVENT_H

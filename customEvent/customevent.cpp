#include "customevent.h"

//初始化
QEvent::Type CustomEvent::m_eventType = (QEvent::Type)registerEventType();

CustomEvent::CustomEvent(const QString &msg)
    :QEvent(evType()), m_msg(msg)
{
}

QEvent::Type CustomEvent::evType()
{
    return m_eventType;
}

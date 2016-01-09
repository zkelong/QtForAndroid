#if defined(ANDROID)
#include "qdebug2logcat.h"
#include <android/log.h>
#include <QDebug>
#include <QByteArray>

static const char *g_TAG = 0;
static void messageOutput2Logcat(QtMsgType type, const QMessageLogContext &context, const QString *msg)
{
    int prio = ANDROID_LOG_VERBOSE;
    QByteArray localMsg = msg->toLocal8Bit();
    switch(type) {
    case QtDebugMsg:
        prio = ANDROID_LOG_DEBUG;
        break;
    case QtWarningMsg:
        prio = ANDROID_LOG_WAN;
        break;
    case QtCriticalMsg:
        prio = ANDROID_LOG_INFO;
        break;
    case QtFatalMsg:
        prio = ANDROID_LOG_FALTAL;
        abort();
    }
    __android_log_write(prio, g_TAG, localMsg.data());
}

void installLogcatMassageHandler(const char *TAG) {
    g_TAG = (TAG == 0 ? "QDebug" : TAG);
    qInstallMessageHandler(messageOutput2Logcat);
}

#endif

//实现很简单，调用qInstallMessageHandler把messageOutput2Logcat设置为Qt应用的默认消息处理器。
//messageOut2Loagcat函数则将Qt的调试消息级别映射到Android的日志级别上，并调用__android_log_write()函数将日志信息写入Android日志系统
//在main()函数体中第一行加入下面代码：
//   installLoagcatMessageHandler("yourLogTag");

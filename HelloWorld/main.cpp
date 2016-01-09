#include <QApplication>
#include <QLabel>
#include <stdio.h>
#include <stdlib.h>
#include <QPushButton>

//把日志信息记录到文件
static FILE *g_log_fp = 0;

static void closeLogFile()
{
    fclose(g_log_fp);
}

static void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    switch(type)
    {
    case QtDebugMsg:
        fprintf(g_log_fp, "Debug: %s (%s:%u, %s)\n",
                localMsg.constData(),
                context.file,
                context.line,
                context.function);
        break;
    case QtWarningMsg:
        fprintf(g_log_fp, "Warning: %s (%s:%u, %s)\n",
                localMsg.constData(),
                context.file,
                context.line,
                context.function);
        break;
    case QtCriticalMsg:
        fprintf(g_log_fp, "Critical: %s (%s:%u, %s)\n",
                localMsg.constData(),
                context.file,
                context.line,
                context.function);
        break;
    case QtFatalMsg:
        fprintf(g_log_fp, "Fatal: %s (%s:%u, %s)\n",
                localMsg.constData(),
                context.file,
                context.line,
                context.function);
        abort();
    }
}

int main(int argc, char *argv[])
{
    //日志文件
    g_log_fp = fopen("my.log", "wt");
    atexit(closeLogFile); //用于关闭日志文件
    qInstallMessageHandler(myMessageOutput);

    QApplication a(argc, argv);
//    QLabel label("Hello world!!");
//    label.show();
    QPushButton *button = new QPushButton("Quite"); //Quite为按钮文字
    QObject::connect(button, SIGNAL(clicked()), &a, SLOT(quit())); //信号与槽
    button->show();
    return a.exec();
}

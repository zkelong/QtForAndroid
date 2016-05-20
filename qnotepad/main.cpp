#include <QApplication>
#include <QTextCodec>
#include "mainwindow.h"
#include "../qDebug2Logcat.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    installLogcatMessageHandler("qnote");
    QApplication a(argc, argv);
    //a.setAttribute(Qt::AA_SynthesizeMouseForUnhandledTouchEvents, false);

    QFont f = a.font();     //Application default font
    f.setPixelSize(20);
    a.setFont(f);   //set font
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));   //文件格式
    MainWindow w;
    w.setAutoFillBackground(false); //
    w.setWindowTitle("qnote");  //window title
#ifndef ANDROID         //build android apk
    w.resize(640,480);  //change window's size
#endif
    w.show();   //运行窗口
    return a.exec();
}

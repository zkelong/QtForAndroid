#-------------------------------------------------
#
# Project created by QtCreator 2014-04-26T13:37:15
#
#-------------------------------------------------
#这个符号注释
QT       += core gui

#比价qt的主版本是否大于4，widgets在5后有单独模块
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Q12    #制定目标文件的名字
TEMPLATE = app  #生成可执行文件，lib库文件


SOURCES += main.cpp\
        Q12Widget.cpp

HEADERS  += Q12Widget.h

CONFIG += mobility
MOBILITY = 

!win32{
  LIBS += -lgnustl_shared
}

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

OTHER_FILES += \
    android/AndroidManifest.xml

#下面是使用例子
CONFIG(debug){  #配置信息，输出信息
    message("debug build");
}

android: message("android version")

equals(TARGET, "Qzip"): message("hit");

#1.注释
#comments
#
#2.组件选择
#QT += core gui widgets
#
#3.模板
#TEMPLATE = app
#
#4.目标文件
#TARGET = xx
#
#5.源文件
#SOURCE += xx.cpp
#
#6.头文件
#HEADERS += xx.h
#
#7.库路径与库
#LIBS += -LC:/abc-Lopencv-ltest  //绝对路径，相对路径，可使用类似Linux中的“:/”
#
#8.头文件路径
#头文件路径
#INCLUDEPATH += c:/abc
#
#9.定义宏
#DEFINES += TEST_XXX
#
#10.变量
#内置变量 QT DEFINES HEADERS SOURCES CONFIG等等
#自定义变量 MY_VAR = xxx
#引用变量 $$VAR_NAME和$${MY_VAR}引用变量
#
#11.函数
#message输出信息
#greaterThan等内置函数
#
#12.代码块与条件测试
#语法：
#<condition>{
#  <commandor definition>
#    ..
#}
#使用配置信息作为条件条件测试
#CONFIG(debug){ //配置信息，
#  message("debug build")
#}
#debug:message("debug build")
#使用平台信息作为条件测试
#android:QT += androidextras
#win32{
#  INCLUDEPATH += c:/protobuf
#  LIBS += protobuf
#}
#使用mkspecs作为条件测试
#android-g++{ //针对平台的工具链。mkspecs目录
#  message("androidid-g++);
#  QT += androidextras
#}
#使用函数作为测试条件
#equals(TARGET, "Quiz") {
#  message("target = quiz")
#}
#进一步学习，Qt帮助索引qmake

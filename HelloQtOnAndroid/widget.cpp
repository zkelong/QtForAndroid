#include "widget.h"
#include <QVBoxLayout>
#include <QLabel>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout * layout = new QVBoxLayout();
    QLabel *hello = new QLabel("Hello Qt on Android!");
    layout->addWidget(hello);
    setLayout(layout);  //Widget指定一个布局管理器
}

Widget::~Widget()
{

}

/*
布局管理器--管理控件位置，将控件放置到合适位置
界面大小变化，控件位置会调整

布局管理器可以嵌套
QVBoxLayout

//继承关系
QLabel->QFrame->QWidget
显示文本或图片
富文本（HTML）
setPixMap() //图片
setMovie()  //gif图片

Qt库部署策略
三种：
Bundle Qt lib in Apk    //打包到APK，布置到手机上，APK比较大
Use Ministro service to install Qt  //在线安装Qt库--有多个APK共享Qt库，节约空间
Deploy local Qt libraries to temporary directory    //适合开发用，临时目录放库
*/

/*
Android配置：
AndroidManifest.xml
Version code: 更新的时候用到，要比旧版本高
Version name: 显示给用户看的
应用图标：
1.低分辨率-中分辨率-高分辨率

选择权限
*/

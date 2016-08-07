#include <QApplication>
#include <QPushButton>

int main(int argc, char * argv[])
{
    QApplication a(argc, argv);
    //链接信号与曹
    QPushButton *button = new QPushButton("Quit");
    QObject::connect(button, SIGNAL(clicked()), //SIGNAL是一个宏
                     &a,SLOT(quit()));  //SLOT是槽,也是宏
    button->show();
    return a.exec();
}

/*
只有QOject才有connect()方法
有好几个重载方法，此处是静态版本。
这里：
第一个参数：发出信号对象
第二个参数：发出的信号
第三：响应对象
第四：响应方法
第五：默认参数（链接方式）--自动链接

信号与槽--观察者模式
MFC采用回调，发送方和响应方相互知道对方

信号与槽 关键字
emit SIGNAL SLOT
*/

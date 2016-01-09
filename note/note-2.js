

/*Hellow World分析
#include <QApplication> //包含头文件
main()中：
    QApplication a(argc, argv);
    --声明了一个QApplication对象a，通过构造函数将命令行参数传递给a，a会解析命令行参数，提取Qt应用框架需要的参数，如"-reverse"(指定UI布局从右向左)。Qt可能会改变命令行参数
    每一个应用，只有一个QApplication实例，必须在使用任何GUI相关资源之前（如QPixmap, QLabel）定义QApplication实例。
    QLabel label("Hello World"); //实例化一个QLabel类的对象，并且将"Hello World!"字符串传递给QLabel的构造函数。
    label.show(); //显示界面，Qt中一个窗口部件创建时都是不可见的，方便我们在它显示前做一些初始化工作。可避免界面的闪烁后突变。
    return a.exec();  //使得应用程序进入Qt的事件循环中，知道用户通过界面交互选择退出程序。

    Qt程序，是事件驱动的。基于Qt框架开发的每一个GUI应用程序、网络服务程序、Qt Quick UI程序，都有一个事件循环，如Win32、MFC或WTL开发GUI应用一样。
    Qt框架能处理各样输入，键盘，鼠标，触摸板，触摸屏，遥控器，轨迹球，移动设备上的按键，网络事件。
    当Qt应用进入事件循环后，Qt框架就监控这些事件，在事件未到达时间里，应用程序处于休眠状态。
    一旦用户单击了鼠标等操作，操作系统就会产生事件（消息），Qt框架捕捉到，并进行一系列转换，最终通过QEvent或信号反馈给你的应用。
    Qt框架对很多默认的处理机制，如HelloWorld里窗口关闭事件。
*/

/*信号与槽
SIGNAL和SLOT两个关键字是Qt框架引用的，其实是个宏定义。
emit也是关键字，用来发射信号的。
QObject::connect(button, SIGNAL(clicked()), &a, SLOT(quit()));
"button"的"clicked()"信号连接到了对象"a"的"quit()"槽上。
点击button，发射"clicked()"信号，"a"的槽"quit()"就自动执行。
信号与槽的连接：是个静态函数
    QObject::connect(
        const QObject * sender,    //发信号的对象
        const char * signal,        //使用SIGNAL宏可以将函数名转换为字符串--"2clicked()"
        const QObject * receiver,   //接收信号的对象
        const char * method,        //SLOT宏将函数名转换为字符串--"1quit()"
        Qt::ConnectionType type = Qt::AutoConnection);  //连接类型
*/

/*布局管理器
    Qt布局系统提供了一种简单却强大的方式来管理一个Widget的所有字Widget，能够根据窗口的大小变化自动安排Widget们的位置。
    Qt提供了一系列的布局类：QVBoxLayout和QHBoxLayout，还有QLayout，QGridLayout，QGroupBox，QFormLayout，QSizePolicy，QStackedLayout，QLayoutItem等类。
QLayout(QWidget *parent),指定parent后，
    这个布局就会作为parent这个widget的顶层布局，无需要再调用setLayout()，而QWidget::layout()也会返回你创建的那个layout。
    一旦为QWidget设置了布局，布局就会负责接管下列任务：
        a.把子widget们安排到合适的位置
        b.自动计算窗口的默认尺寸
        c.自动计算窗口的最小尺寸
        d.尺寸变化处理
    当widget的内容变化时自动更新调整整个UI布局，下面变化会引起布局调整：
        a.字体、文本以及其他内容
        b.隐藏或显示一个子widget
        c.移除某些子widgets
常见布局：
    QHBoxLayout：水平布局，左向右，右向左
    QVBoxLayout：垂直布局
    QGridLayout：表格布局
    QFormLayout：表单布局，“标签-值”风格，在一个两列的表格内安排widget。
使用布局：
    可以向布局中添加widget、layout、stretch、space等元素。
    widge，QWidget及其子类的实例们，它们只能找一个QWidget（或期派生类）的实例作为parent，而不能找布局实例。
    布局是一系列辅助类。QWidget和QLayout共同的祖先QObject，它会控制它所有后裔的生命周期，会适时销毁它子孙。
控件：
    Qt中，QWidget是一切窗口小部件的祖宗。
    Widget是用户界面的最小单位，从系统中接收键盘，鼠标和其他事件，把自己绘制到屏幕上。
    每个widget都是矩形的，在窗口管理系统中以一定的Z序存在，所以可能相互遮住。
    操作系统都有一个全局的窗口管理器。
    窗口管理器用来管理窗口的Z序、窗口之间的相互遮罩修剪、窗口的默认风格、窗口的装饰部件等。

    加入一个Widget没有父亲，那么这就是顶层窗口，可以调用setWindowTitle()设置它的标题，setWindowIcon()来设置它标题栏的图标。

    QWidget需要绘制，不然只有个背景，无法可视。QPushButton，QLabel，QComboBox继承自它，自定义Widget需要继承它。
    QWidget需要处理事件，如键盘，鼠标，触摸屏等事件。
*/

/*常用控件介绍
QLabel:
    无用户交互功能。显示内容：
        a.纯文本。 setText(QString)
        b.富文本。 如用HTML标记文本，支持着色，加粗等，使用setText(QString)。QLabel会自动探测文本格式，也可以显示调用setTextFormat()方法指定显示格式。
        c.图片。   setPixmap(QPixmap)
        d.动画。   setMove设置一个QMovie（GIF动画）
        e.数字。   setNum() 设置整型（int）或双精度浮点数（double）
        f.空文本，不显示什么。
    控制QLabel外观：
        a.对齐方式: setAlignment()
        b.边框风格: setFrameStyle()
        c.控制缩进: setIntent()
        d.文本与边框之间的间隙: setMargin()
        e.设置手在单词边界处断行: setWordWrap()
QPushButton:
    命令按钮。
    可显示文本标签，文本前使用“&”来设置快捷键，想显示符号“&*，用“&&”
    设置外观：setText(), setIcon(), setFlat(), setDisaled()等
    禁用按钮：setDisabled()方法。
    给按钮设置菜单：setMenu()。
    信号：
        clicked(bool checked)
        pressed(), released()
    继承自：QAbstractButton
    兄弟：单选按钮（QRadioButton），复选按钮（QCheckBox），工具栏按钮（QToolButton）
        这些都可以用setCheckable()来设置是否可以选中。
QComboxBox:
    下拉选择框
    设置：insertItem(), insertItems(), seCurrentIndex(), setItemText(), setItemIcon(),
    访问：itemText(), itemIcon(), currentText()
    可否编辑：setEditable()
    维护自定义数据：setItemData(), itemDataa()
    可提供一个itemDelegate来接管每个item的绘制。
QMessageBox:
    模态对话框。
    Qt提供供的消息类框
    提供了一组静态方法abount()、infomation(), warning(), critical(), question()以便我们快速创建消息框。
    也可以生成自己的QMessageBox实例，然后调用addButton()添加按钮，调用setText()设置文本，调用setIcon()设置图标...，调用exec()显示消息框。
*/

/*Qt代码风格
1.类名：大写字母开始，单词间用驼峰命名法（Camel-Casing）
2.方法名：小写字母开始，单词间驼峰命名
3.宏：全大写字母，单词间下划线分隔
4.属性interval的getter和setter方法命名为interval(getter)和setInterval(setter)。这是命名getter和setter的通用做法。
*/

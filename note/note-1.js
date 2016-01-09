.pragma library

/*Qt 开发组件
应用程序：
1.Qt widgets Application:
    基于Qt Widgets的应用，可选包含词汇表可以基于Qt Designer进行设计的ui文件。Qt SDK中历史悠久的项目模板，Qt5前的主角
2.Qt Quick Application:
    基于Qt的GUI编程，允许悄创建混合QML和C++应用。可以用QML编写界面的便利和快捷以及它内嵌的炫酷效果，
    又可以利用C++代码实现诸如密集计算等对性能要求较高的模块。
3.Qt控制台：
    不带界面的Qt应用模板，可以用于服务器软件或者简单的命令行小工具软件。
4.HTML5应用：
    5.0后新增，可以创建一个同时包含HTML5和C++代码并包括一个WebKit试图的HTML5应用程序。混合Web和Native编程。

库：
1.C++库：
    包含两种，一种是动态链接库,Windows下的dll文件，UNIX、Linux、android等平台下的so文件；
    一种是静态库，一般式.a文件，Windwos下也可能是.lib文件。
    Qt还在标准动态链接库的基础上，定义了一组适合Qt插件框架的接口，实现这种接口的库也可以由这个模板生成。
2.Qt Quick 1 Extension Plugin:
    Qt 4.7.9版本后，可以使用QDeclaretiveEngine类加载一个C++插件来动态扩展应用的功能。这个模板就是用来创建这种插件的。
3.Qt Quick 2 Extension Plugin:
    Qt 5.0及以后版本，可使用QQmlEngine类加载一个C++插件来动态扩展应用的功能。这个模板就是用来创建这种插件的。
4.Qt Creator插件：
    创建一个自定义的QT Creator插件，可以按照你的想法来扩展Qt Creator的功能。

其他向项目；
1.Qt 单元测试:
    为某个类或者某个功能创建一个基于QTestLib的单元测试。单元测试帮助你验证代码可用并且没有倒退。
2.Qt4 设计师自定义控件：
    创建一个Qt Designer自定义控件或则一个自定义控件集合。构建出来的控件，可以在Qt4设计师中使用，就像Qt内建的标准控件一样。
3.空的Qt项目：
    如果你只想利用Qt SDK中的构建项目功能而不想使用任何Qt类库，则可使用此模板，创建一个基于qmake的空白项目，然后根据你的需要，实现任意你想要的功能。
4.子目录项目：
    特殊的项目模板，创建的项目，目的是为了包含其他项目，以便你包项目组织成树形结构，便于管理。
5.Code Snipet:
    我们在编码的时候，经常遇到一些重复性的工作，编写一些类似的或者雷同的小代码片段，我们需要一种方法将这些代码管理起来，减少重复输入。这就是Code Snipet的技术。
    它在粒度上比项目或者库更小，可以进一步提高工作效率。代码片段项目模板创建一个基于qmake的测试项目，以便你能输入一个代码片段。

Assinstant
    用来查看在线文档的工具。SDK API...
    开始菜单中可以找到，也是Qt Creator的帮助。

Designer
    Qt工具，帮助你用Qt Widget设计和构建图形用户界面（GUI）。使用Designer，可以所见即所得的方式设计和定制我们的窗口、对话框，而且可以使用不同的风格和分辨率测试他们的效果。
    Assinstant索引"Using a Designer UI File in Your Application"，就可以学习如何把Qt Designer生成的UI文件与代码结合。
    可以使用Qt Desinger设计界面布局，调整控件的ID、文字等基本信息，还可以编辑控件的信号与槽等。

Linguist
    预言家是Qt提供的用于应用程序软件国际化的工具，可以把待本地化的文本转换成任何一种语言，然后编译成Qt应用可以使用的qm文件。
    为了使用Linguist，Qt应用必须标记哪些文本需要翻译，使用lupdate工具生成TS文件供Linguist使用；也必须在应用启动后加载qm文件以便程序可以使用对应的语言向用户显示信息。
    用Assinstant索引"Internationalization with Qt"

命令行环境：
    Qt SDK提供了一个命令行环境，给那些特殊需求的开发者，方便他们在不是用Qt Creator集成开发环境的情况下编译他们的应用程序。
    qmake: Qt SDK提供的一个工具，用来分析项目文件，生成项目所需要的Makefile。
    例子：把main.cpp拷贝到另一个目录，用命令行环境，cd切换到目录
        1.Qmake-project //创建项目文件(.pro)
        2.Qmake         //创建一个Makefile(可以在qmake后显示的写项目文件的名字，如HelloWorld.pro)
        3.mingw32-make  //根据Makefile构建项目，生成一个可执行文件。

*/

/*Qt for Android 环境搭建
1.JDK，需要设置环境变量
2.Android SDK
3.Android NDK
4.Apache Ant：用来自动编译Android项目的工具。
5.选项->Android配置。
6.构建和运行，AVD创建
7.链接手机：命令行窗口中输入"adb devices"，查看是否能找到你的设备。
*/

/*Qt库的部署策略
Build Android APK
3种部署策略：
1.Use Ministro service to install Qt
    Ministro是BogDan Vatra创建和维护的开源项目。
    不用把所有东西都打包进你的APK，安装包只需要包含你的应用库文件(.so文件)、它需要的资源以及它需要的外部依赖库列表。
    应用启动时，会尝试链接Ministro服务，如果是失败，会认为没安装，进而打开设备上的默认的市场应用，让用户安装Ministro。
    成功后，你的应用会把依赖库列表发给Ministro服务，不存在就下载确实的库并保存到一个特定的安全位置。然后它会将另外一份列表发送给你的应用，包括你的应用在启动Qt应用前必须加载的所有依赖项。
  优点：
    a.多次安装Qt应用，用户只需要下载一次Qt库，或更新缺少的库。
    b.可以检测设备的CPU特性（armv5 with VFP或者armv7 with NEO)，下载针对该CPU特性集优化果的Qt库版本。可以让应用运行更流畅。
    c.Ministro可以自动更新Qt库，而不需要发布一个新的应用。
    d.可以用一个APK匹配所有的安卓平台。apk小，Ministro会下载与目标设备CPU架构匹配的Qt库。
    e.可以定制Ministro源码以便你使用自己定制的Qt库。你只需要一个Web服务器来创建和上传Mnistro仓库。
  缺点：
    a.必须要安装一次Ministro服务
    b.更新Qt库可能带来不良影响(比如兼容性问题、Qt库自身的Bug)，还是比较安全的。
2.Bundle Qt libs in APK
    在APK中捆绑Qt库，除了你的应用库文件和资源文件，Qt Creator还自动添加你应用所需要的所有Qt库
  优点：
    a.包含运行需要的一切
    b.可以定制Qt版本，加上产品上市，不必为了修复你产品的重大Bug而等官方版本的发布。
    c.Qt库不会在后台更新，不用担心你的应用突然出现问题
    d.Qt库可以使用应用商店提供商的基础服务，Ministro不能确定是否能够支撑一个超级成的应用。
    e.使用Google Play(或其他应用市场)，下载时会使用设备上的通用机制，就算你的应用挂起了，也在也会在后台进行，进度显示状态栏上，遵循用户设置，不会在使用移动数据链接时下载和更新。
  缺点:
    a.Apk大，Qt库很大
    b.所有的Qt库必须解压，应用需要更多的空间来运行。
    c.因为体积太大，你不能在一个APK中匹配多个目标平台，必须给每个平台（armv5、armv7、x86）创建一个APK，版本维护麻烦。
    d.不能在armv5上使用VFP，不能在armv7上使用NEON。
    e.Qt库不能自动更新。
3.Deploy local Qt libraries to temporary directory
    这个部署策略主要被Qt开发者在研究Qt库本身时使用，因为它是在设备上部署和测试，修改果的Qt库的最快方式。不要在正式产品中用它。
*/

/*Qt日志
Qt提供了4个全局函数用于输出调试信息或警告信息
1.qDebug()      //用于输出以调试为目的的信息
2.qWaring()     //用于报告程序的可恢复性错误
3.qCritical()   //用于输出严重的错误信息和报告系统错误
4.qFatal()      //用于在程序退出前输出一些简短的致命错误信息
上面4个函数，都可以用像使用C语言中的printf()函数一样使用，除qFatal()，还可以使用流输出运算付"<<"来输出信息。
如：qDebug("ap startup, pid - %d", getpid()); qDebug() << "ap startup, pid - %d" << getpid();
默认情况下，Qt会把你掉用的qDebug()等函数输出的信息送往标准输出或标准错误，而qFatal()的默认处理，还会结束你的应用。
我们可以调用qInstallMessageHandler()函数来注册自己的消息处理器，替换Qt框架提供的默认消息处理器。
qInstallMessagehandler()接受一个QtMessageHandler类型的参数，也返回之前的消息处理器（可能为NULL）。QtMessageHandler其实是一个函数指针，使用typedef做了类型定义。

main()中注册自己的消息处理器
qdebug2logcat.cpp把日志输出到Android日志系统中
adb工具查看日志
adb logcat，查看手机或其他设备上输出的所有日志。
adb logcat -v time，让日志带时间信息
adb logcat -v time -s Tag，只显示标签为qnote的日志信息，同时显示日志时间。如果想同时过滤多个标签，可以用英文半角逗号分隔标签，如adb logcat -v time-sqnote,test。
*/

/*Qt Pro文件介绍
1.注释符号 #
2.组件选择：
    在项目文件中，变量一半用来保存一个字符串列表。对于比较简单的来说，使用qmake的内建变量就可以胜任项目的构建。qmake支持一系列的内建变量，如QT
  QT: 用来声明Qt库的。
    greaterThan(QT_MAJOR_VERSION, 4): QT += widgets //greaterThan是qmake所支持的一个内建函数
    QT_MAJOR_VERSION则是qmak的一个内建变量，这行的意思说，Qt的主版本大于4时，给项目添加QtWidgets这个模板。在Qt5前没有独立的QtWidgets模块，Qt Widgets包含在QtGui模块中。
    默认包含core和gui模块，只需要声明其他模块就行了。
    语法：Qt+=模块缩写
    可通过QT变量添加的模块包括：core, gui, widgets, network, xml, quick, multimedia, webkit等。
    Assistant索引"variables", 完整列表。
    还支持： QT-=模块缩写  去掉项目不需要的模块，如只是想开发控制台程序，就可以在项目文件中添加 QT-=gui
3.目标文件名：
    TARGET变量用来设定项目的目标文件名，不设置，目标文件名会被自动设置为跟项目文件一样的名称。
    想给Debug和Release版本取不同名字：
    CONFIG(debug, debug|release) {
        TARGET = HelloWorld_d
        message("debug build")
    } else {
        TARGET = HelloWorld
        message("release build")
    }
4.模板
    TEMPLATE变量用来设定项目的构建类型。不设置，qmake会默认按应用（TAMPLATE = app）来构建你的项目。
    目前qmake支持的模板：
    app，默认模板，qmake会生成一个构建应用的Makefile。
    lib，库，qmake会生成一个构建动态库或静态库的Makefile
    subdirs，子目录项目，qmake会根据SUBDIRS变量生成一个Makefile，该Makefile包含构建子目录的逻辑，子目录内必须由pro文件存在
    vcapp，qmake会生成一个适用于Visual Studio的项目文件(.vcproj文件或类似文件)，能够用Visual Studio打开并构建一个应用。
    vclib，qmake会生成一个适用于Visual Studio的项目文件(.vcproj文件或类似文件)，能够用Visual Studio打开并构建一个静态库或动态库。
    vcsubdirs，qmake会生成一个适用于Visual Studio的解决方案文件(.sln文件或类似文件)，里面包含每个子目录对应的项目文件(.vcproj文件)。可以使用Visual Studio打开解决方案并构建每个子项目。
5.指定源文件：
    SOURCE+=源文件
    多个源文件可以用空格隔开，写不下用"\"来折行，可以使用"+="
    如果你不知道一个变量是否包含有默认值，比较安全的做法是采用"+="来进行设定。
6.指定头文件：
    HEADERS+=头文件
    用法与SOURCE一样。
7.设置头文件路径：
    开发中经常用到第三方库的头文件，或者我们自己积累的类库，此时就需要在Qt项目文件中指定这些类库的头文件目录。
    INCLUDEPATH，使用类似SOURCE，可以折行"\"，可以用"+="，如果路径中包含空格，用双引号保护起来。
    INLCUDEPATH += e:/protobuf-2.0/src \
                e:/media/vlc-1.1.1.11/sdk/include
    Windows和Linux(like)平台路径分隔符不太一样，不过没关系，Qt项目文件都可以支持，可统一使用”/“作为分隔符。
8.指定库与库文件
    有时候项目会引入第三方库，或者为了模块化开发而把大的项目拆分，把一些模块编译成动态库进行复用。LIBS就可以完成这件事。LIBPATH同样，但Qt5.2中已经过时，不建议用
    如果路径包含空格，使用""保护起来
    #Linux like
    LIBS += -L/usr/local/lib -lmath \
        -L/usr/lib -lz
    # windows
    LIBS += -Le:/vlc-1.11/sdk/lib -lvlccore
9.定义宏
    可用DEFINES来定义宏
    用法类似LIBS
    DEFINES += LIVE_TEST
    DEFINES += DEBUG_CONNECTION
    DEFINES += TEST_STUB
    qmake为Android平台而定义的宏--ANDROID
    对于复杂的项目，可能还会通过qmake支持的条件语句、内建函数以类似编程的方式来更好的控制构建过程。可以在Assistant索引qmake学习
10.配置信息
    CONFIG变量用来设定项目的配置信息和编译选项。qmake内建了很多选项供CONFIG变量使用。
    qt, CONFIG变量默认包含这个配置，去掉用 CONFING -= qt
    release, 让qmake构建Release版本
    debug, 让qmkae构建debug版本
    debug_and_release，让qmake构建Release和debug版本。release，debug，debug_and_release这几个选项，哪个是最后一个配置，就使用哪个。
    warn_on，让编译器显示尽可能详细的警告信息。强烈建议打开，因为很多时候一些看似无关紧要的警告会带来莫名其妙的运行期错误。
    warn_off，让编译器不显示警告信息。war_on，war_off，哪个后配置哪个生效。
    CONFIG变量还有个好处：支持自定义配置，然后根据自定义配置控制构建过程
        CONFIG += auth win32select iocp
        然后可以根据自定义的CONFIG配置在项目文件中写下面的代码
        CONFIG(auth) {
            SOURCES += login/login.cpp \
                common/licence.cpp
            HEADERS += login/login.h  \
            common/licence.h
        }
        CONFIG是qmake内建的一个测试函数
11.代码块与条件测试
    Qt项目文件中的代码块，与C语言的if类似，一个条件测试紧跟着一对花括号"{}"。条件测试为真时，括号中的声明语句就会被执行。
    <conditon> {
        <conmmand or defintion>
        ...
    }
    注意：左括号"{"必须和条件测试语句在同一行。右括号"}"单占一行。
    例：
    win32 {
        SOURCE += win32select.cpp
    }
    win32: qmake内建变量，表示Windows平台构建项目时，win32select.cpp添加到源文件中编译。
    类似的变量还有：unix, macx, android
    也可以在条件测试语句中使用"!"符号，逻辑非
    可以嵌套：
    win32 {
        CONFIG(debug, debug|release) {
            SOURCE += winDebug.cpp
        }
    }
    配置信息：
        CONFIG变量，既可以用qmake内建的选项，也可以使用自定义的值来配置你的项目。重要的是，qmake对CONFIG变量的值进行特别处理，CONFIG变量中的每一个值都可以用在代码块中作为条件测试语句。
        CONFIG += d3d
        d3d {
            TARGET = render_d3d
            DEFINES += HAVE_DIRCTX
            SOURCE += d3d_render.cpp
            HEADERS += d3d_render.h
        } else {
            TARGET += render_gl
            DEFINES += HAVE_OPENGL
            SOURCE += opengl_render.cpp
            HEADERS += opengl_render.h
        }
    平台信息：
        可以使用Qt SDK中的mkspecs目录（Qt5.2.0、mingw48_32/mkspecs）下与平台和编译器相关的规格信息来进行条件测试。
        所谓mkspecs，就是一些配置文件，定义了平台相关的工具链信息，说明在哪个平台上应该使用哪个编译器、连接器等进行编译；
        也可以在配置文件中定义一些特定的编译选项、宏、头文件路径、库文件路径、默认的附加连接文件等。
        那些在mkspecs目录中出现的mkspec目录名，都可以用于代码块钱的条件测试。
        例：当为Android平台编译时，添加特定的用于调试的源文件和宏：
        android-g++ {
            DEFINES += NO_STL
            RUNTIME_LIBDIR = /system/lib
            DEFINES += ANDROID_DEBUG
            SOURCES += android_debug.cpp
        }
12.变量
    前面用到的SOURCE, HEADERS, QT, CONFIG, DEFINES其实就是qmake的内置变量，我们可以在项目文件中用"=, +=, -="等操作符改变它们的值。
    Assistant索引"variables"或者"qmake"
    定义自己的变量，使用"="即可，如： MY_VAR = TEST
    qmake一遇到不认识的名字，就会建立一个新的变量，使用左值作为变量名，右值作为变量的值。
    不管是自定义变量，还是qmake内建变量，都可以在项目文件中引用。
    使用"$$"符号有"$$MY_VAR"和"$${MY_VAR}"两种方式。$$MY_VAR把一个变量的值赋值给另一个变量；
    而$${MY_VAR}除用于赋值（与$$MY_VAR一样)外，还可以用于放在字符串中间来拼接变量值，与其他字符串之间可以没有空格，而$$MY_VAR的前面如果与其他非空字符串连接在一起可能无法识别。
    如：
        VLC_INC = "D:/vlc-1.11/sdk/include"
        MEDIA_INCLUDE = $$VLC_INC
        INCLUDEpATH += $$VLIC_INC
      用$${MAY_VAR}拼接库和头文件路径
        VLC_INC = 1.11
        VLC_SDK = d:/media/vlc-$${VLC_INC}/sdk
        VLC_INCLUDE = $$VLC_SDK/inlcude
        VLC_LIBPATH = $$VAL_SDK/lib
*/

/*pro.user文件
是个XML文件，用于保存Qt Creator生成的与你目录相关的配置。比如你的构建套件、构建目录、中间文件目录、运行设置、构建步骤、清理步骤等。
*/

/*pri文件
可以认为是Qt项目文件的头文件。
可以使用include()函数把它包含进你的pro文件中，基本上pro文件中支持的元素和语法，都可以在pri文件中使用。
通常我们在pri文件中编写一些通用的配置选项，以供我们的多个项目使用，以免去重复设置的麻烦。如多项目复用的源码、宏定义、中间文件路径、安装路径等。
假如我们想在多个项目中使用一个库，处于某种目的又不想以动态库的形式使用，只想把源代码嵌入到项目中，那么就可以为这个库建立一个pri文件，把相关的源文件组织起来，在你的多项目的pro文件中都包含这个pri文件即可。
例：
    include(libnet.pri)
*/

/*Makefile
Makefile文件根据一定的规则来描述一个源文件如何编译、源文件与头文件之间的依赖关系、中间文件如何链接、目标文件要安装到哪里、重复编译时那些文件需要编译那个不需要编译。
有了Makefile在结合make工具，就可以自动化项目的编译过程了。Makefile手动写是手艺活儿。
Qt creator中qmake会根据项目文件生成Makefile
*/

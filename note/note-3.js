

/*元对象系统(Meta-Object System)
  三个重要关键特性：
    a.用于对象间通信的信号与槽机制
    b.运行时类型信息
    c.动态属性系统

    运行时类型信息，运行应用程序在运行时获取某个对象的元数据，如获取类名，获取父类的元数据，查询某个信号的索引位置，某个方法的索引位置，某个属性。
    这是使用QObject::connect()建立信号与槽之间连接的基础，如果你在连接时指定一个不存在的信号或槽，那么程序运行期间会出现找不到某信号的警告信息。

    动态属性系统，两个含义：
        a.编译期间声明的属性可以哟动态行为，如发出信号、在脚本系统中使用等。
        b.运行程序在运行是根据需要向某个对象添加属性。（c++的类属性都是静态的，一旦编译完成后就不可增减，而Qt实现的动态属性系统，允许我们随时添加，删除属性，这样数据传递、保存、获取有极大的灵活性）
            实现基于3件事：
                @.QObject类提供了元对象系统的框架实现，所有享受元对象系统便利的类，都必须是QObject的派生类
                #.在类声明的开始，私有访问去，放置Q_OBJECT宏，这个宏定义会启用元对象系统的特性，如信号与槽，动态属性等。
                $.元对象编译器（the Meta_Object Compilier, 简写为moc)为QObject的派生类提供必须的代码来实现元对象系统的特性。
*/


/*Q_OBJECT宏
    想要使用信号与槽，动态属性，国际化等Qt提供的功能，就必须继承QObject类并在派生类的类声明尅是的private区域内放置Q_OBJECT宏
    Q_OBJECT在Qt SDK的qobjectdefs.h中定义
    Q_OBJECT做的事情有：
        1.定义一个静态的元对象staticMetaObject。
        2.重载QObject类定义的虚函数metaObject。
        3.重载QObject类定义的虚函数qt_metacast()。
        4.国际化支持，QT_TR_FUNCTIONS会被展开为tr()和trUtf8()两个函数，以便可以对类中需要做国际化粗粒的字符串使用它们
        5.重载QObject类定义的虚函数qt_metacall()
        6.定义静态函数qt_static_meacall()
*/

/*QMetaObject
    QMetaObject被设计用来保存Qt对象的原信息。当你继承QObject类并使用Q_OBJECT宏后，类就有了一个静态的QMetaObject实例staticMetaObject。
    它会保存定义类中所有的元信息，如：类名、信号的名字与索引、槽的名字与索引等等。这是我们可以使用信号与槽的根基所在。
    常用的QMetaObject类的方法：
        className(): 返回类名
        superClass(): 返回父类的元对象
        method()和methodCount()提供了一个类的信号与槽及其他可以通过名字调用的成员方法的信息。
        enumerator()和enumeratorCount()提供一个类内定义的枚举类型的信息。
        propertyCount()和property()提供一个类的属性信息。
        constructor()和constructorCount()提供一个类的构造函数的信息。
    Qt的元对象类似Java的反射机制，只要能闹到一个对象的元对象，哪怕你不知道这个类定义，也可以构造一个实例出来进而调用新生实例的方法。这就是反射机制的基本原理。
*/

/*信号与槽关键字
    使用信号与槽时，离不开signals, slots, emit, SIGNAL, SLOTS这5个关键字。
    1.signals
        定义信号的关键字。signals: void bloom();
        C++中只有访问控制修饰符public, private, protected可以如上使用。
        SDK中qobjectdefs.h文件，signals关键字实际上是个宏定义： define signals protected
    2.emit
        emit bloom()
        qobjectdefs.h中，emit是个宏定义：define emit --是个空宏，其实就是C++中普通的函数调用。
    3.slots
        定义槽的关键字：protected slots: void onBloomTme();
        slots也是个空宏。
    4.SIGNALS
        其实是宏定义："2"#a
        它使用C语言中的字符串拼接符把你传入的信号名字转化成了一个以数字”2“开始的字符串。如：SIGNAL(clicked())--"2clicked()"
        做了这样的转换，Qt在调用调用信号时，才能查找元数据找到对应信号。
    5.SLOTS
        与SINALS类似，宏定义： "1"#a
        SLOTS(onBloomTime())得到字符串："1onBloomTime()"。
        Qt会解析这个字符串，根据类型索引1和名字onBloomTime在元数据中查找是否有你所说的这个对象。

    使用signals关键字，在它面前什么也不加，connect()函数要的信号、槽都是字符串而我们却只提供了函数名。
    这几个关键字的定义，一方面作为助记符方便moc工具扫描头文件提取信号与槽函数，另一方面方便开发人员使用、阅读代码，达到望文生义的效果。
*/

/*moc的魔法
    moc在make阶段被调用，根据头文件生成一个moc_xxx.cpp文件。
    1.moc_penoy.cpp源码
        项目目录下搜索可得。
    2.moc干的事情：
        a.扫描文件，根据signals和slots关键字提取信号与槽的名字以及对应的索引信息，保存到一个全局变量qt_meta_stringdata_Peony中。
        b.为类的方法、信号、槽、属性、枚举类型等建立各种元信息，保存到全局数组qt_meta_data_Peony中。
        c.实现Q_OBJECT宏定义的函数，初始化Q_OBJECT宏定义的类型为QMetaObject的静态实例staticMetaObject，把前面提取的各种元信息以及实现的函数都关联到staticMetaObject实例上
        d.为Peony类的信号bloom()和wizen()生成模板代码。
*/

/*信号的真容：
    emit是空宏，信号就是函数。
*/

/*信号与槽的链接：
    1.建立联系：QMetaObject::activate()是QMetaObject类的内部方法
    。。。
*/

/*信号与槽深入理解
    1.信号与槽原理
        信号与槽时Qt对象间通信的一种机制，是Qt核心特性，也是Qt与其他应用框架的最显著区别。
        在一些比较老的GUI框架中，使用回调函数来完成这种通信。
        回调函数是C语言的函数指针的一种应用，它哟两个根本缺陷：不能保证持有回调函数业务处理函数会使用正确的参数来调用回调函数指针;回调函数是的业务处理函数和回调函数紧密耦合，因为业务处理函数必须要知道应该调用哪个回调函数指针。
        而Qt的widget有很多预定义的信号，我们可以继承widget来添加自己的信号，槽是一个函数，在响应一个特定的信号时被调用。
        Qt的widget有很多预定义槽，我们也可以继承widget来添加自己的槽以便处理我们感兴趣的信号。
        信号与槽机制是类型安全的：接受信号的槽的签名必须与信号的前面匹配（实际上槽的参数可以比信号少，Qt保证槽被调用时忽略多余的参数）。因为签名是兼容的，编译器可以帮助我们坚持类型不匹配的问题。
        信号与槽的链接是基于字符串的，QObject::connect()函数的实现会在连接时检测信号和槽的类型是否匹配。
        信号与槽是松散耦合的：发出信号的类既不知道也不关心哪个槽接收信号。
        信号与槽是一个观察者模式的实现。
    2.在类中定义和使用信号与槽
        a.从QObject类或它的派生类继承，如果是多次继承，必须把QObject放在第一位
        b.在类声明的一开始放置Q_OBJECT宏（紧接着左大括号，什么都别添加），它会帮忙定义Qt系统必须的变量和方法。
        c.使用signals关键字声明信号，切记不要实现与信号同名的函数。
        d.使用slots关键字声明槽，切记一定要实现槽
        e.对象状态改变需要发出信号是，使用connect()函数，connect()函数有很多重载形式，只需要记住静态版，原型：
            connect(const QObject * sender, const char * signal, const QObject * receiver, const char * method, Qt::ConnectionType type = Qt::AutoConnection)
*/

/*信号与槽的链接类型
    Qt::ConnectionType枚举定义了如下链接类型：
    AutoConnection，自动链接（默认值）。
        会将连接类型的判断延迟到信号发射时，如果槽与信号在同一个线程环境，槽被直接调用，效果与DirectConnection相同；
        如果槽与信号分属两个线程，则和QueuedConnection相同，通过向槽所在线程发送QMetaCallEvent来异步调用槽。
    DirectConnection，直接连接。信号发射时，槽被直接调用。非线程安全，不要在连接分属两个线程的信号与槽时使用此种连接类型。
        非要在跨线程的信号与槽之间得到阻塞式同步体验，使用Blocking QueuedConnection来替代。
    QueuedConnecetion，队列连接。信号发射时不会离开调用，而是向拥有槽的接受者所在的线程发送一个QMetaCllEvent事件，当该线程的时间循环分拣出该事件时才执行。槽是在接受者的线程环境中执行。
    BlockingQueuedConnection，阻塞式队列连接。当信号发生时，会阻塞住信号所在线程，一直到接受者所在线程执行了槽之后才解除阻塞，其他逻辑与队列连接一致。
        只在跨线程的信号与槽之间使用这种连接类型。
*/

/*信号与槽使用经验
    1.信号与对象的特定状态对应
    2.一个嘻哈可以和一个槽连接
    3.一个信号可以连接多个槽（观察者模式都这样）
    4.一个槽可以接收多个信号（只要函数签名匹配）
    5.槽的参数必须和信号类型匹配
    6.槽的参数个数可以少于但不能多于信号的参数个数
    7.连接信号与槽时，不需要考虑访问控制，因为是基于字符串连接的。
    8.信号与槽的链接是动态的，是运行是发生的。
    9.信号与槽的链接是可以断开的，使用disconnect()函数。
    10.信号可以连接信号，但槽不能连接槽
    11.信号与槽可以分处于不同的线程环境中的对象，此种场景请显式指定连接类型为Qt::QueuedConnection
    12.跨线程的信号与槽连接，实际是通过QApplication::postEvent()完成槽的调用的，因此槽的调用一般发生在槽所属对象所在的线程环境中
    13.QObject::sender()可以获取发送信号的对象，但是这违反了面向对象编程的基本原则，除非你的槽连接了多个信号，否则不要使用。
        另外还要注意，如果连接类型时QueuedConnection，你调用sender()是要么得不到发送信号的对象，要么得到一个已经销毁的对象的指针而导致访问错误。
*/


/*属性系统
    Qt的属性系统，既允许我们使用Q_PROPERTY()宏定义期的静态属性，有允许我们可以在运行期通过setProperty()动态增加属性。
    一.静态属性
        要想在一个类中使用Q_PROPERTY()宏声明一个属性，该类必须是QObject的后裔；同时也必须在类体的开始引入Q_OBJECT宏。具备这两个条件就可以来了解Q_PROPERTY()宏。
        Q_PROPERTY(type name
            (READ getFunction  //如果你没有位属性指定MEMBER标记，则READ标记必不可少。声明一个读取属性的函数
            [WRITE setFunction] | //可选配置。声明一个设定属性的函数，指定的函数，只能有一个参数，必须返回void
            MEMBER memberName [(READ getFunction | WRITE setFunction)]) //如果你没有位属性指定READ函数，就必须为其关联一个成员变量，这样的话这个成员变量不用指定READ/WRITE函数就可以读写。当然，如果想控制其读写，也可以指定READ/WRITE函数
            [RESET restFunction] //可以选配置。为了让一个属性回滚到与其上下文匹配的默认值
            [NOTIFY notifySignal] //可选。给属性关联一个信号（该信号必须是已经在类中声明过的），当属性的值发生变化时就会触发该信号。为MEMBER变量指定的NOTIFY信号最多只能有一个参数，而且类型必须与属性的类型一致。当信号触发是，它的参数就是属性的新值。
            [REVISION int] //可选。将属性导入到QML中使用时指定的，它指定了属性使用的API版本。默认为0
            [DESIGNABLE bool] //可选。用来说明一个属性是否可以被Qt Designer使用，默认值为true。也可以使用一个返回布尔值的函数
            [SCRIPTABLE bool] //可选。说明一个书信是否可以被脚本引擎访问，默认true
            [STORED bool]   //可选。表明一个属性是独立存在的，还是从其他属性值衍生出来的，默认值为true
            [USER bool]     //可选。表明一个书信是否设计为面向用户的或用户可编辑的。一般地，一个类之类有一个USER标记为true的属性。默认为false
            [CONSTANT] //可选。表明一个属性为常量。一个标明属性为常量。一个标明为常量的属性不能有WRITE函数和NOTIFY信号
            [FINAL])    //可选。表明一个书信不能被派生类修改。moc工具不会检查一个FINAL标记为true的属性是否被派生类修改，因此实现这要自己小心被在派生类中修改它。

        QWidget的例子：
            Q_PROPERTY(bool visible READ isVisible WRITE setVisible DESIGNABLE false)
                声明了类型为布尔值的visible属性，可以通过isVisible函数访问，通过setVisble(bool)函数来改变它，这个属性在Qt Designer中不可见。

        READ, WRITE, RESET等标记指定的函数，可以是继承来的，还可以是虚函数。如果是多重继承，则必须来自第一个继承类。必须是类中存在的函数。QPROPERTY()不会生成这些函数。
        属性类型可以是QVariant支持的任何类型。也可以是用户定义的类型，只要包含响应的头文件即可
        Q_PRPERTY()的参数中不能包含逗号，逗号会被认为是宏参数分隔符。所以如果一个属性的类型时QMap，就不能把QMap<QString, QString>直接放在宏内。

        设置属性：
            用setProperty()方法通过属性名字来访问。
            QPushButton * button = new QPushButton(this);
            QObject * object = button;
            button->setFlat(true);
            object->setProperty("flat", true);
          如果通过名字设定一个属性时改名字对应的属性不存在，它会建立一个属性，并将其值设定为你传的值，这就是动态属性。

          例子：
            class PixmapButton : public QWidget
            {
                Q_OBJECT
            Q_PROPERTY(QPixmap momalImage READ normalImage WRITE setNormalImage)
            Q_PROPERTY(QPixmap focusImage READ focusImage WRITE setFocusImage)

            public:
                void setNormalImage(QPixmap normal) {
                    m_mormalImage = normal;
                    update();
                }
                QPixmap normalImage() const {
                    return m_nomalImage;
                    if(isVisible()) update();
                }
                void setFocusImage(QPixmap focus) {
                    m_focusImage = focus;
                    if(isVisible()) update();
                }
                QPixmap focusImage() const {
                    return m_focusImage;
                }
            private:
                QPixmap m_normalImage;
                QPixmap m_focusImage;
            };
    二、动态（运行时）属性
            使用QObjcet的setProperty()方法动态为一个对象增加属性。
            调用setProperty()需要提供属性的名字和值，
                1.如果你提供的属性名字存在并且提供的值的类型与Q_PROPERTY()声明时指定的类型匹配，那么setProperty()就会修改这个属性；
                2.如果值的类型失配，这次调用会被忽略
                3.如果不存在指定名字的属性，setProperty()就会新建一个属性并保存它的值。然后可以通过property()方法用之前的名字取回这个属性的值。
**/


/*事件和事件过滤系统
    事件分发过程：
      1.QCorApplication::notify()函数
      2.应用过滤器
      3.对象过滤器
      4.QObject::event()函数
      5.特定事件处理函数，如keyPressEvent()等。
    当某个事件发生，你可以有5种方式作出响应。1，2种方式使用需谨慎，容易出问题。通常用2~5种方式。
      1.重新event()
        event()函数是QObject类处理事件的入口，是一个虚函数，可以重载它来拦截感兴趣的事件。只需要关注感兴趣的事件，其他事件必须交给父类的event()函数。
      2.重写特定事件处理器
        如Adroid的返回键，可以通过keyPressEvent()、keyRelieaseEvent()
        例：
        void MyWidget::timerEvent(QTimerEvent * e)
        {
            if(e->timerId() == m_iMoveTimer)  //定时器事件QTimerEvent, timerId()可返回一个定时器事件的标识，以区分不同的定时器
            {
                //caculate position(x,y)
                move(x, y);
                return;
            }
            return QWidget::timerEvent(e);
        }
      3.事件过滤器
        Qt允许你拦截分发给某个对象的事件，实现拦截的对象就是事件过滤器。
        作为事件过滤器的类，必须是QObject类的子孙，通过重写QObject类的eventFilter()方法来接受事件以作选择性处理。
        原型：
            bool QObject::eventFilter(QObject * watched, QEvent * event);
        名为watched的对象，事件原本是要发给它的，但是安装了过滤器后，事件就会先发给过滤器对象。过滤器对象表态不处理某个事件时，这个事件才会进一步向前投递，才可能达到watched对象。
        安装过滤器：
            void QObject::installEventFilter(QObject * filterObj);
        filterObj-就是实现了eventFilter()方法的对象。
        一个filterObj可以被安装到多个被过滤的对象上。
        笔记实例中有运用
      4.自定义事件
        如：跨线程通知我们自己开发的其他类库。使用自定义事件在对象之间通信，比信号与槽更加灵活一些，可以携带更多的上下文数据。
        图片浏览器实例中就包含了ImageLoadedEvent自定义事件。
        实现自定义事件的步骤：
            a.继承QEvent
            b.定义事件类型（取值在QEvent::User和QEvent::MaxUer之间，建议使用registerEventType()函数来让Qt自动选择一个全局唯一的事件类型，可以避免冲突）
            c.在需要用自定义事件发出通知的类或方法中，用sendEvent()或postEvent()发送事件。
            d.在需要处理自定义事件的类中，重写QObject::event()来处理事件。
        自定义事件类声明：
            class ErrorEvent : public QEvent
            {
            public:
                ErrorEvent(int err, const char * desc);
                int errorCode() const;
                QString errorDescription() const;
                static Type eventType();        //静态方法，可以在重写的event()函数中使用。采用eventType()这种方式可能存在多线程竞争中初始化问题。
            protected:
                static Type m_evType;  //静态变量，可以用来判断事件类型，在类外初始化是通过registerEventType()为m_evType赋值。
                int m_iError;
                QString m_strError;
            }
        定义事件类型：
            QEvent::Type ErrorEvent::m_evType = QEvent::None; //初始化，当m_evType取值时，调用registerEventType()函数来获取一个全局唯一的时间类型值
            ErrorEvent::ErroEvent(int err, const char * desc)  //构造函数初始化列表中，调用eventType()函数把其返回值作为事件类型传递给父类QEvent。
                : QEvent(eventType()), m_iError(err), m_strError(desc)
            {
            }
            QEvent::Type ErrorEvent::eventType()
            {
                if(m_evType == QEvent::None)
                {
                    m_evType = (QEvent::TYpe)registerEventType();
                }
                return m_evType;
            }
        发送事件：
            Qt向一个对象发送事件有两种方式：sendEvent()和postEvent()。使用MFC或者Win32编程时，对应的有SendMessage()和PostMessage()两种向特定窗口发送消息的方式。
            QCoreApplication::sendEvent()方法是阻塞的，它发送事件给接受对象并且等待对方处理完毕后才返回。原型：
                bool QCoreApplication::sendEvent(QObject * receiver, QEvent * event);
                    receiver：接收事件的对象指针；event：发送对象的指针
                sendEvent()发送的事件对象不会自动销毁，需要记得在合适的地方干掉。当sendEvent()返回true时，说明你发送的事件被处理了，反之，没人睬你。
            例：多行文本向下滚动一行：
                QTextEdit * edit = getEdit();
                QkeyEvent down(QEvent::keyPress, Qt::Key_Down);
                QCoreApplication::sendEvent(edit, &down);
            QCoreApplication::postEvent()方法是异步的，它向事件队列中登记一个指定接受者的事件，然后立即返回。
            使用postEvent()发送的事件，在下次Qt的主事件循环运行时会被分发给指定的对象。需注意，使用postEvent()发送事件，事件对象必须从堆上分配，而且不能随意删除。一旦调用了postEvent()，事件对象的一生就托付给了Qt框架，它会在适当的时候销毁事件对象。
            postEvent()原型：
                void QcoreApplication::postEvent(QObject * receiver, QEvent * event, int priority = Qt::NormalEventPriority);
            它比sendEvent()方法多一个优先级参数，一般人用不上它，所以Qt给了中庸的默认值Qt::NormalEventPriority.
            poostEvent()是线程安全的，可以从一个线程向另一个线程发送事件，sendEvent()不是线程安全。
                QTextEdit * edit = getEdit();
                QKeyEvent * down = new QKeyEvent(QEvent::keyPress, Qt::Key_Down);
                QCoreApplication::postEvent(edit, down);
        处理事件：
            重写event()函数。
            对于自定义事件，必须重写event()函数来处理。
            bool DownloadMainWindow::event(QEvent * event)
            {
                if(evetn->type() == ErrorEvent::eventType()
                {
                    event->accept();
                    ErrorEvent *ee = (ErrorEvent *)event;
                    if(ee->errorCode() == 0)
                    {
                        //some other code
                    }
                    else
                    {
                        qDebug() << "erro - " << ee->errorDescription();
                    }
                    return true;
                }
                retrun QWidget::event(event);
             }
**/

/*定时器事件
    定时器作用：
        定时处理任务（如定时检测版本更新）
        替代循环（比如某些APK要等SD卡就绪后可写才能干活）
        分时多任务
        动画效果
        ......
    定时器精度依赖于操作系统的时钟精度。
    不能保证会按时发生，Qt事件循环有时可能在干别的事（如一个繁杂的计算任务或者复杂的绘图事件）而过了它该发生的时刻，于是要么晚些时候发生，要么被认为过期而无视
    反过来，不要在定时器中处理特别复杂好事的实务，它会阻塞住Qt的事件循环让Qt没法处理其他事件。

    Qt使用定时器事件的两种方式：QTimer和QObject::startTimer()

    1.使用QTimer
        QTimer类继承自QObject类，支持周期性（默认）或一次性定时器（需调用setSingleShot()方法设置）。
        在定时器触发时，QTimer发射timeout()信号。可以吧实现的类某个槽连接到QTimer对象的timerout()信号上。
            QTimer *timer = new QTimer(this);
            connect(timer, SIGNAL(timerout()), this, SLOT(updateCaption()));
            timer->start(1000);  //理论上每秒触发一次，周期性触发的定时器
        QTimer提供了两个名为singleShot()的静态函数，一次性使用定时器，不用创建QTimer对象。
            一个可以指定定时器类型（根据精度区分），一个不能指定精度类型，使用平台相关的默认精度。常使用不带精度的版本。
            void QTimer::singleShot(int msec,  //多少秒后触发
                    const QObject * receiver,  //指明接收定时器timerout()信号的对象
                    const char * member)  //槽
    2.使用QObject::startTimer
        相对于QTimer类，使用QObject::startTimer()开启定时器是比较原始的方式。原型：
            int QObject::startTimer(int interval,   //单位是毫秒
                        Qt::TimerType timerType = Qt::CoarseTimer);  //默认类型-只保证指定周期的5%精度。
        startTimer()方法返回一个整型的id，用来标识定时器，通常你需要保存它以备后用（用来杀掉已开启的定时器或区分不同的定时器）
        定时器会周期性触发，直到你使用QObject::killTimer(int id)方法将其干掉。
        使用startTimer()开启定时器，必须重写timerEvent(QTimerEvent *event)或者event(QEvent *e)函数来处理定时器事件QTimerEvent。
            //开启定时器
            m_timer = startTimer(1000);
            ...
            //重写timerEvent处理QTimerEvent事件
            void MyClass::timerEvent(QTimerEvent *e)
            {
                if(e->timerId() == m_timer)
                {
                    doSomething();
                    //一次性定时器，不调用killTimer则为周期性
                    killTimer(m_timer);
                    m_timer = 0;
                    return;
                }
                renturn QObject::timerEvent(e);
            }
        Qtimer与QObject::startTimer()来开启定时器：
            QTimer对象会占用相对较多的内存，启动多个定时器，则会占用更多内存；而QObject::startTimer()方式，一个定时器值话费一个int型数据的存储代价。
**/


/*对象树与生命周期
    使用Qt类库是，很多类的构造函数，都有一个parent参数。
    构造一个对象是为其指定父对象，这是Qt类库的一个显著特点。
    查看QObject类的源码，内部有个d_prt成员变量，类型时QScopedPointer<QObjcetData>，而QObjectData内部有一个QObjectList类型的名为children的成员
    children链表，存储了一个QObject对象的所有孩子。
    构造对象时指定了父对象，那么该对象就会被加入父对象的children链表中，当父对象销毁时，会遍历孩子链表，尝试销毁每一个孩子。

    QObject对象在析构时，会断开所有信号与槽连接，删除所有孩子，吧自己从父对象中移除出去。
    创建对象没指定父对象，该销毁时销毁，可能导致内存泄露。

    QObject类中有一个属性：objectName
        Q_PROPERTY(QString objectName \     //Q_PROPERTY宏定义
                    READ objectName \
                    WRITE setObjectname \
                    NOTIFY objectNameChange)
        可以通过objectName()方法获取对象的名字，通过setObjectName()设定对象名字，当对象名字发生改变时会有信号：objectNameChange().
        对象的名字属性，就可以用于查找对象，查找对象方法：findChild()和findChildren()，一个返回单独对象，一个返回对象列表。
        例：
            //返回名为"button1"，类型为QPushButton的孩子
            QPushButton * button = parentWidget->findChild<QPushButton *>("button1");
            //返回类型为QListWidget的孩子
            QListWidget * list = parentWidget->findChild<QListWidget *>();
            //直接孩子
            QPushButton *button = parentWidget->findChild<QPushButton *>("button1", Qt::FindDirectChildOnly);
            //返回所有名为"widgetname"的QWidget类型的孩子列表
            QList<QWidget *> widgets = paretnWidget.findChildren<QWidget *>("widgetname");
            //名为"button1"或"Button1"的
            QPushButton *button = parentWidget->findChild<QPushButton *>(QRegExp("[Bb]utton1"));
**/

/*智能指针
    C++常在类的构造函数中分配资源，在析构函数中释放资源，这种做法是RAII（Resource Acquisition Is Initialization）机制的一种。
    若无智能指针，必须保证new出来的对象在合适的时候被delete。
    虽然C++没有语言层面的GC，不能像Java无视资源管理，但智能指针可以在很大程度上解放我们，可以把我们从资源管理的泥沼中拖出来。
    1.QPointer
        QPointer<T>, 模板类，监视QObject及其派生类的指针。QPointer重载了"*, /, -, <"等操作符，你可以像使用普通C++指针一样使用QPointer。
        测试指针指向的对象是否存在：isNull()    //如果你保留的是C++原始指针，它指的对象在别处被删除是，指针变为野指针，对它的访问会造成内存错误。
        例：
            QPointer<QLabel> label = new QLabel("&Status");
            ...
            if(label) { //if(!label.isNull()), if(label != 0)
                label->show();
            }
    2.QSharePointer
        QSharePointer<T>，内部使用了引用计数，当QSharePointer对象被删除时，如果它持有的指针没有被别的对象引用（引用计数为0），则该指针（所指对象）会被删除。
        一旦原始指针被一个QSharePointer对象管理，则该指针不应当被直接传递给另一个QSharePointer对象，并且不能直接在别处删除该指针。
        而QSharePointer对象可以安全地在各个模块间传递，可以通过“=”操作符或者拷贝函数将一个QSharePointer对象传递给另一个，此时内部引用计数会增加，直到所有的QSharePointer对象被删除，该对象才被删除
        当你不关注一个对象在何时何处被删除，而有希望自己使用时不被删除，同时希望不用时被自动删除，可以使用QSharePointer。即一个对象需要在多个模块间传递，使用并保证其能够适时被释放。
    3.QWeakPointer
        QWeakPointer<T>对C++指针进行了弱化引用，不能直接直接解引用来使用原始的C++指针，当时可以通过isNull()，!()等方法来判定原始的C++指针是否有效
        可以通过QWeakPointer的data()方法拿到原始指针，但不能保证拿到的C++指针在使用时不被别的模块删除。
        QWeakPointer一般是从QSharePointer对象或另一个QWeakPointer对象创建，若直接调用无参构造函数，创建一个指向nothing的QWeakPointer对象，无实际意义，只能在其他地方使用"="赋值。
        QWeakPointer维护的指针如果指向QObect及其派生类，作用同QPointer。
        多数时候必须和QSharePointer使用，用起来较为麻烦，很多人宁愿使用简单的QPointer.
        QWeakPointer可以升级为QSharePointer使用（使用QWeakPointer::toStrongRef()方法或QWeakPointer拷贝函数或QWeakPointer的"="操作符，但你需要判断升级后的QSharedPointer是否为空。
            QSharedPointer<Status> status(new Status);
            QWeakPointer<Status> weakRef(status);
            QSharedPointer strong weakRef.toStrongRef();
            QSharedPointer strong2 weakRef;
            if(strong)
            {
                strong->printStatus("Weak promote to striong");
            }
            else
            {
                qDebug() << "weak promote to strong but " \
                    "Status object had been delete";
            }
    4.QScopedPointer
        QScopedPointer包装了使用new操作符在堆上动态分配的对象，能够包装动态创建的对象在任何时候都可以被正确的删除。
        QScopedPointer一旦获取了对象管理权，你就不能错它哪里要回来了。而且独占管理权，从不考虑转让给被的对象或只能指针。
        QScopedPointer可用于多出口函数中的对象动态资源的管理，尤其从满了各种判断条件，return满天飞的函数。
        QScopedPointer可以定制删除策略，内置了4中删除器：
            a.QScopedPointerDeleter， 使用delete删除有new分配的对象。--默认
            b.QScopedPointerArrayDeleter，使用delete[]删除由new[]分配的对象。
            c.QScopedPointerPodDeleter，使用free()删除由malloc()分配的对象。
            d.QScopedPointerDelteLater，针对QObject及派生类的对象，使用deleteLater()来延迟删除对象。
        可以实现自己的删除器，只需在删除器中提供一个静态成员函数：void clieanup(T *pointer)。
    5.QObjectCleanHandler
        QObjectCleanHandler很有用的辅助类，它是QPointer和QScopedPointer的合体
        QObjectCleanHandler可以监视多个QObject对象的生命周期。当被监视的对象在别处被删除时会自动从QObject中移除，可以通过isEmpty()来判定QObjectCleanHandler中是否还有对象。
        删除所有被监视的对象：clear()   //析构时也会删除
        可以作为资源清理器使用，若你有在一个多出口函数中有多个QObject（或派生类）对象需要管理，就可以使用它。
*/

/*动态类型转换
	当你在在即的类声明中使用了Q_OBJECT后，就可以使用：动态类型转换
	QBOJECT有个方法inherits(const char* className)，可以判断一个QObject类（或其派生类）的实例是否从给定的名字的类继承而来。
	例：
		QPushButton *button = new QPushButton(widget);
		button->inherits("QObject"); //true
		button->inherits("QWidget"); //true
		button->inherits("QAbstractButton"); //true
		button->inherits("QLayoutItem"); //false
	若想在确认一个对象的类型后做与该类型相关的事情，最好是使用qobject_cast()函数。它是模板函数：
		template<class T>
		inline T qobject_cast(QObject * object)
		{
				typedef typename QtPrivate::remove_cv<yptename \
					QtPrivate::remove_pointer<T>::type ObjType;
				Q_STATIC_ASSERT_X(\
					QtPrivate::HasQ_OBJECT_Macro<ObjectType>::Value,
					"qobject_cast requires the type to have a Q_OBJECT macro");
				return static_cast<T>(reinterpret_cast<T>(object) \
					->staticMetaObject.cast(object);
		}
	qobject_cast()会把给定的QObject类型转换成你想要的类型，失败返回0.
	qojbect_cast()认为一个类是他自己的派生类（可以用inherits()方法判断一下）
	使用：
		QObject * object = new QPushButton(widget);
		//button == (QAbstractButton*)object
		QAbstractButton * button = \
			qojbect_cast<QPushButton *>(object);
		//radio == 0
		QRadioButton *radio = \
			qobject_cast<QRadioButton *>(object);	
**/

/*国际化
	Qt提供了Qt语言家（QtLinguist）、lupdate和lrelease来进行翻译处理。
	lupdate用以提取项目源文件黄总可翻译文本，生成公语言家使用的ts文件；
	lrelease根据ts文件，生成最终的公应用程序使用的qm文件；
	Qt Linguist是图形化工具，加载ts文件，将防疫结果写入ts文件，也可以调用lrelease生成qm文件。
	要使用Qt的国际化机制，最好在类中声明中使用Q_OBJECT宏，这样可以在你类方法中使用tr()函数标记待翻译的文本。
	如果不使用Q_OOBJECT宏，只能使用QOject类的静态版本的tr()方法，不优雅，敲字多，生产效率不高，还可能无法区别不同上下为环境下相同文本需要不同译本的情况。
	1.字符串国际化方法
		a.对于UI界面的字符串，使用QObject::tr()函数，使用Q_OBJECT宏的QOject派生类中可以直接使用tr()方法。非QObject派生类可以使用QBject::tr()或QCoreApplication::translate()方法。非QObject派生类可以使用QBject方法。
		b.使用QT_TR_NOOP或QT_TRANSLATE_NOOP标记需要翻译的文本，然后使用tr()。
		c.使用QString::arg()来拼接字符串，在arg()方法内使用tr()。
	2.创建译本
		a.在工程文件中添加TRANSLATIONS变量，以qnote.pro为例：TRANSLATIONS = qnote_zh_CN.ts.qnote_EN.ts
		b.打开Qt命令行环境，进入qnote项目目录，执行命令“lupdate qnote.pp”, 就会生成pro文件中TRANSLATEIONS指定的ts文件。
		c.使用Qt语言家（文件菜单-打开子菜单）打开ts文件，人工翻译，保存（ts文件为xml文件，可以使用文本编辑器编辑它）
		d.单击Qt Linguist文件菜单中的发布子菜单，生成译文文件qnote_zh_CN.qm; 也可以代开Qt命令行环境，切换到ts文件所在目录，使用“lrelease qnote_zh_CN.ts”来生成译文文件。
	3.装载译文文件
		创建了qm文件，在程序黄总加载特定语言的译文文件。
			int main(int argc, char *argv[])
			{
				QAppliction a(argc, argv);
				...
				QTranslator translator();
				translator.load("qnote_zh_CN.qm");
				a.installTranslator(&translator);
				...
				return a.exec();
			}
		实际开发中国，需要检测系统语言系统（QLcale来检测），还可能有多个模块都有译文文件（可以定义多个QTranslator实例，每个实例记载一个译文文件，然后都按装到QApplication的实例上）
		Qt框架本身针对不同语言也有译文文件，如果你使用了QT框架的某些默认组件，如消息框，想要让它上面的文字与系统语言环境一致，也应当加载Qt的译文文件。
		Qt文档中有详细说明，索引“internationalization”。
	4.运行是改变语言
		运行软件时，改变语言。通过检查语言变化来实现。
		当语言变化时，Qt框架会产生一个类型为QEvent::LanguageChange的事件，可以重写QObject::changeEvent(QEvent*)方法来处理它。
			比如可以重新装载译文文件，然后把需要国际化的文本更新一下。
		例
			void YourWidget::chagneEvent(QEvent *event) 
			{
				if(e->teyp() == QEvent::LanguageChange)
				{
					titleLabel->setText(tr("Document Title"));
					...
					okPushButton->setText(tr("&OK"));
				}
				else
				{
					QWidget::chageEvent(event);
				}
			} //把不处理的事件交给父类处理
		
		
**/
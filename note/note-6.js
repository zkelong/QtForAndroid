/*多线程
	《Win32多线程程序设计》
**/

/*上路吧，线程
	class SimpleTread : public QThread
	{
	protected:
		void run()
		{
			qDebug() << "hello thread - " << QThread::currentThreadId();
		}
	};
	int main(int argc, char *argv[])
	{
		QApplication a(argc, argv);
		SimpleTread *thread = new SimpleTread();
		thread->start();
		return a.exec();
	}
*/

Qt中使用多线程：
1.继承QThread类
2.重写run()虚函数        
3.构造线程对象。
4.调用QThread::start()即可开启新线程

QThread是Qt提供的底层线程类，代表一个线程对象，具有创建新线程的能力，通过其start()方法，可以启动一个线程。
QThread对象能够开启新线程，但它本身所处的线程，和新线程不是同一个线程。

Qt中每个QObject对象都关联唯一一个线程环境。这种关联一直保持到它死去或者被moveToThread()强行迁徙到另一个线程中。
不同线程环境中的对象不能发展父子关系。

Qt类的构造函数都有一个父对象参数。

三个概念：
1.对象：QObject及其派生类的实例
2.线程对象：特指QThread及其派生类的实例(母鸡)
3.线程：由线程对象开启，不与线程对象在同一个线程中(蛋)

QThread::run()函数是可以控制可以塑造的线程函数。线程函数，这里特指线程的主函数，即在新线程中运行直到线程结束的函数，类似main()函数

线程对象和线程的生命周期：
线程对象的生命周期比线程的生命周期长。

CountDown例子：
CountThread较SimpleThread复杂：
1.调用exec()开启自己的事件循环
2.新线程中创建对象timer和firer
3.3.跨线程连接信号与槽


开启事件循环的作用：
1.本线程内使用信号与槽，就像在UI线程中使用的那样
2.本线程内对象间传递事件，postEvent()、sendEvent()
3.本线程内对象的槽连接到其他线程环境内的对象的信号上，也可连接本线程环境中对象的信号到其他线程环境中的对象的槽
4.可从其他线程环境中向新线程环境中的对象（使用postEvent()方法）发送事件。
5.可以使用Qt框架中一些需要事件循环的类库，    如QTimer、QTcpSocket、QTCPServer、QUDPSocket、QProcess、QNetworkAccessManamger、QNetworkReply

线程间通讯：
两个概念：
1.主线程：把QApplication或QCoreApplication所在的线程，通常是main()函数所在线程
2.工作线程：其他的，使用QThread派生类的实例（线程对象）开启的线程

主线程和工作线程之间的通讯，有两种方式：
1.跨线程使用信号与槽
2.跨线程发送事件

线程对象与主线程中创建它那个对象同属一个线程，即主线程，因此，如果在QThread派生类中定义信号与槽并使用它们连接主线程中的其他GUI组件或对象，本质上不是夸线程通信
在主线程run中创建的对象，与主线程中的对象就分属两个线程。

获取主线程中对象的指针来连接信号与槽：
1.1.通过线程对象这个中介完成，像countdown中那样
2.提供全局的方法配合同步机制。

跨线程事件：
线程通过exec()开启事件循环，线程中对象，就可以重载QObject::event()函数（或其他特定事件函数，如timerEvent()）来处理事件。

线程投递事件：
1.一个线程：QCoreApplication::sendEvent()
2.线程间：QCoreApplication::postEvent()

对象在哪个线程，它的事件就发生在哪个线程，它的event()函数就在哪个线程中被调用。

线程同步：
QLabel可以播放动画

线程同步
Qt提供了丰富的线程间同步机制，4种：
1.Qmutex
2.QSemphore
3.QWaitCondition
4.QReadWriteLock             查帮助
Qmutex:
	确保多个线程对同一个资源的顺序访问，提供了lock()、tryLock()、unlock()等方法
	默认是非递归的，通过构造函数可以在创建时指定为递归。
	递归模式允许已有持有互斥量的线程再次通过lock()方法进入资源保护区，而非递归模式则不允许这么做。
	Qt还提供了QMutexLocker辅助类方便QMutex的使用，这样不用担心多分支多出口的函数中不小心死锁
QSempore：
	是Qt的信号量的实现。用于维护多个资源的竞争访问，如果资源数量为1，则其行为就退化为QMutex一样。
	构造函数接受一个参数，指定当前可用的资源个数，默认为0.
	acquire()获取资源、release()释放资源。可以一次获取/释放1个，也可1次获取/释放多个。
	tryAcquiire()，允许指定等待时间。
	
使用QThread的注意事项：
1.父子对象必须处在同一个线程中，QThread对象不能是它启动的那个线程中创建的对象的父。
2.依赖事件循环的对象只能在同一个线程中使用。如果想把某个对象放在特定的线程中使用，可以调用moveToThread()方法
3.工作线程中创建的对象必须在线程对象被删除之前删除。有两个方法：
	a.在run()函数的栈上创建工作者对象，由工作者对象担任所有其他对象的父，这样工作者在run()结束时自动被销毁，它的孩子们也会被销毁。
	b.在栈上创建一个QObject Cleanup Handler或者QScopedPointer来管理从堆上分配的对象，依靠这些在run()结束时会自动析构的智能指针来删除其他对象。
4.尽量不要在栈上创建QThread派生类实例，然后启动线程——如果你的线程不能再拥有线程对象的函数结束前结束，有灾难。
5.尽量和谐地结束一个线程，然后再销毁线程对象。比如，可以调用QThread::quit()通知一个线程准备结束，然后调用QThread::wait()等一下。

线程池(QThreadpool):
	每个Qt应用都有一个全局的线程池，可以通过QThreadPool::globalInstance()访问。
	QTreadPool的start()方法可以接受一个QRunnable派生类的实例，然后调用约定的run()方法执行它不了解也不关心的任务。
	QRunnable有个纯虚函数run()，派生类必须实现它才能完成一些实际的事情。
	QRunnable的setAutoDelete()方法可以设定或取消QRunnable对象的阅后即焚的属性（默认是阅后即焚），一般QThreadPool调用完QRunnable::run()就会干掉该对象。想改变这种默认行为，在调用QThreadPool::start()方法前通过setAutoDelete来设置，如果在那后面，不知道会发生什么事，线程可以随意切换的。
	QThreadPool还提供了一系列函数让你维护线程池，如setExpiryTimeout()可以设定空闲线程的存活期（如果不设置，过30秒就退了）；setMaxThreadCount()可设定线程池内的最大线程个数，而reserveThread()又可以超过限制预留一个线程出来；clear()可以清除还未执行的任务；waitForDone()可以等待所有线程退出。

高阶多线程API：QtCouncurrent
	使用QtConcurrent编写程序，能够根据设备的CPU核心数量自动决定使用的线程个数，这样开发的应用能够自动利用将来更先进硬件设备的强大性能。
	QConcurrent命名空间提供了一系列的高阶API，使得你不用使用QThread、QThreadPool、QMutex、QSemphore、QReadWriteLock、QWaitCondition等低阶类库就可以方便地进行多线程编程。
	引入新文件头<QFutureWatcher>，QFutreWatcher类可以用来跟踪一个QFuture对象，看任务是否完成。
	图片加载例子。
	
	
	


















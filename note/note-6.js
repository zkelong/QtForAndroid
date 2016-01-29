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
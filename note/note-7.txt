/*网络编程	
**/

Qt SDK5.2的世界里，底层的socket编程依然是QTcpSocket和QUDPSocket。
而上层应用协议的编程变得更加简单了，针对HTTP、FTP等常见协议。只需要使用统一的网络访问管理类库QNetworkAccessManager即可。

Qt中，针对上层应用协议的网络访问API，就是围绕QNetworkAccessManager进行的。
QNetworkAccessManager对象，可以使用它提供的一组标准方法来发送网络请求，而每个方法都会返回一个QNetWorkReply对象，这个对象代表了你发送的请求相应的反馈，即可以读取网络应答的元数据，又可以读取实体数据。
QNetworkAccessManager的get(), post(), head(), put(), deleteResource(), sendCustomRequest()等方法可用于发送网络请求，http、ftp、https都小菜一碟，只要构造一个QNetworkRequest对象传递给它们就行。

1.http编程：
QNetQNetworkAccessManager的接口及其枚举类型Operation，还有QNetworkRequest的接口及其KnownHeader、Attribute等枚举类型，为http设计。
QNetworkAccessManager也支持下载、上传等常见的ftp操作。
httpTestTool例子
QNetworkAccessManager网络编程常涉及的4个类：
	1.QNetworkAccessManager是中心，它提供了发送请求的各种API以及网络配置相关的方法
	2.QNetworkRequest代表一个网络请求，包括URL、HTTP访问用的User-Agent、用户名，密码等都听过它设置
	3.QNetworkReply是QNetworkAccessManager根据你提交的QNetworkRequest构造的一个应答对象，一旦请求发出，就可以通过它获知网络操作过程中的各种状态。
	4.QUrl是构造请求（QNetworkRequest）时常用的类，可以编码URL，提取URL中的主机、路径、文件、用户名、密码等信息。
	http下载相关的槽，这些槽都是为了响应QNetworkReply的信号而定义的：
		onMetaDataChanged()将会连接到metaDataChanged()信号上来获知元数据的变化（HTTP状态码、内容类型和长度等）
		onFinished()会连接到finished()信号；
		onDownloadProgress()连接到downloadProgress()信号，可以方便地实现进度条更新。
		onUploadProgress()连接到uploadProgress()信号，上传文件时用到
		onReadyRead()连接到readyRead()信号上以便读取数据
		
2.QTcpSocket/QTcpServer
很多读者熟悉socket编程，在Qt中，QTcpSocke和QUdpSocket对应了我们常见的两种socket交互方式：面向连接的和无连接的。
QTcpSocket是异步的
QTcpServer是QAbstractSocket，而QAbstractSocket继承自QIODevice.QTcpSocket既拥有QAbstractSocket的connected()、disconnected()、error()、
	
	
	





/*Qt模板库介绍
    Qt提供了一系列的模板容器类，可以用来存储特定的元素。C++标准模板（Standard Template Libray, STL）也提供了一系列的容器类。可以使用这两者中的任一种。
    Qt模板库有两个好处：在所在的平台上拥有一致的行为；使用隐式共享。
*/

/*QString
    在内部使用隐式共享（copy-on-wtrite），节省内存和避免不必要的数据拷贝。
    Qt开发尽量使用QString而非别的字符串处理类库（比如STL中的std::string）。可以避免你的程序依赖Qt以外的而其他框架。优点：
        a.使用与Qt框架本身所使用一样的字符串处理类、辅助类，可以减少你的应用的体积。
        b.支持多个平台，不用考虑字符串类库的平台兼容性。（如Android平台默认没有携带STL实现）。
        c.可以共享Qt框架对字符串类库的效率提升，如隐式共享。
        d.始终面向同一个字符串接口编程，代码针对不同平台只需重新编译而不用因为替换字符串类库而反复改写。

        不用担心内存分配以及关于'\0'结尾等注意事项。与C风格字符串不同，QString中间可以包含'\0'符号，length()函数会返回整个字符串的长度，不仅仅从开始到'\0'的长度。


    1.初始化字符串
        a.传递一个const char *给QString的构造函数。
            QString str = "Hello"; QString str("Hello");
        b.构造一个QChar类型的数据，传递给QString的构造函数。
            static const QChar data[4] = {0x0055, 0x006e 0x10e3, 0x3a3};
            QString str(data, 4);
              QString会对QChar数据做深拷贝，将data传递给QString后就可以在你想要的任何时候修改它的内容而不会影响变量str的内容。
        c.使用resize()函数设定QString实例的大小，然后逐个字符进行初始化。就可以使用C/C++数组那样，使用[]操作符，用从0开始的索引来访问QString的内部数据，[]操作符返回指定索引位置的内部数据的一个引用，可以访问和修改它。
            QString str;
            str.resize(4);
            str[0] = QChar('U');
            str[1] = QChar('n');
            str[2] = QChar(0x10e3);
            str[3] = QChar(0x03a3);
            如果想只读访问，可使用at()方法，比[]操作符快得多。

    2.操作字符串数据
        append(), prepend(),insert(), replace(), remove(), operator[]()。
        QString str = "and";
        str.prepend("rock "); //str == "rock and"
        str.append(" roll");  //str == "rock and roll"
        str.replace(5, 3, "&");  //str = "rock & roll"
        如果想逐步构建一个字符串并且提前知道它有多长，可以使用reserve()函数让QString给你预分配一定大小的内容。这会避免频繁地、零散地分配内存，大大提高新能。
        截取字符串：
        QString str = "I am fine, thank you";
        QString tmp = str.mid(5, 4);  //tmp == "fine"
        QString left4 = str.left(4);  //left4 == "I am"
        QString right3 = str.right(3);   //right3 == "you"
        去除字符串两头的空白字段：trimmed()
        去除字符串两头空白字段，把中间连续的空白字符替换为单个空格：simplified()
        字符串转换为数字：toInt(), toDouble()（C代码需要使用atoi()或sscanf()来完成类似的转换）
        数字转换为字符串：setNumber(), number()等函数以便把数字转换为字符串
        大小写转换：toLower(), toUpper()

    3.字符串查询
        查找字符串：indexOf(), lastIndexOf()
        QString str = "We must be <b>bold</b>, very<b>bold</b>";
        int j = 0;
        while ((j = str.indexOf("<b>", j)) != -1) //indexOf第二个参数：开始寻找位置
        {
            qDebug() << "Found <b> tag at index posintion" << j;
            ++j;
        }
        查看实例是否以某个字符串开始或结束：startWith(), endsWith()
        包含某个字符串：contains()
        比较字符串：compare()
        QString 还重载了"==", "!=", ">", ">=", "<", "<="等操作符：
            int a = QString::compare("def", "bac"); //a > 0
            int b = QString::compare("abc", "def"); //b < 0
            int c = QString::compare("abc", "abc"); //c == 0

    4.编码转换
        编码格式之间可自由转换：toUtf8(), toUcs4(), fromUtf8(), fromUtf16()
            QByteArray ba = strInput.toUtf8(); //to urf8 byte array
        和QTextCodec结合，QString还可以进行更为复杂的编码转换。下面把字符串转换为GB2312编码，然后再转换为Percet-encoding(用于URL访问)
            QTextCodec * codecGB2312 = QTextCodec::codecFormName("GB2312");
            QByteArray ba = codeGB2312->fromUnicode(strInput);
            QByteArray byteArrayPercentEncoded = ba.toPercentEncoding();
            //label is an instance of QLabel
            label->setText(QString(byteArrayPercentEncoded));
    5.格式化输出
        QString提供了一个sprintf()函数，实现与C语言中printf()函数一样的格式化输出功能：
            str.sprintf("%s %.1f", "fps:", 90.2);
        QString另一个格式化字符串函数arg()
            QString url = QString("http://%1:%2:%3")      //%1、%2、%3为占位符，将根据arg()的参数类型进行展开，参考QString帮助手册
                            .arg(host)
                            .arg(port)
                            .arg(path);
*/

/*容器类
    Qt提供了一系列容器类，可以用来替代STL，有跨平台、隐式共享等好处。
    1.QList<T>
        可以用类似数组下标一样的索引访问这些值。
        添加元素：append(), prepend()/insert(), push_from(), push_back()
        访问元素：at(), [], value(), last(), first(), front(), back()
        元素个数：length(), size(), count(), isEmpty()
        摘走元素：takeAt(), takeLast(), takeFirst()
        测试包含指定元素：indexOf(), lastIndexOf(), contains(), startsWith(), endsWidth()
    2.QLinkeList<T>
        与QList<T>类似，更倾向使用迭代器来访问其中的元素。元素多时，插入元素效率高于QList<T>。
        有更好的迭代器，一个指向QLinkedList内元素的迭代器，只要元素存在迭代器就有效，而QList的迭代器，只要发生任何的插入或删除操作吗，就会失效。
    3.QVector<T>
        在内存中的相邻位置存储一组元素，看起啦像数组那样。在QVector的前面或中间插入一个元素会很慢，因为它会导致大量的数组元素需要移位。
    4.QStack<T>
        QVector<T>的派生类。提供了后进先出（LIFO--Last In First Out）的栈式操作。相比QVector<T>增加了pop(), push(), top()等方法。
    5.QQueue<T>
        QList的派生类，提供了先进先出（FIFO--First Input First Output）的队列式操作。相比QList增加了enqueue(), dequeue(), head()等方法。
    6.QSet<T>
        代表了数学中的单值集合，支持快速查找。
    7.QMap<T>
        提供了一个字典（关联数组），将类型为Key的key映射到类型为T的value上，就是键-值对，一个key对应一个value。QMap存储的数据是按Key排序的。
        如果数据顺序不重要，QHash<T>是一个效率更高操作更快的选择
    8.QMultiMap<Key, T>
        与QMap的API几乎一样，但是有更快的查询操作，存储的数据是无序的
    9.QMultiHash<Key, T>
        QHash的派生类，针对多值散列提供了更好的接口。
    在Qt帮助，索引“container classes”，查找更多容器类用法。QVector系列容器与QList系列容器类似。而QMap系列与QHash系列类似。
*/

/*
    QList的迭代器使用起来就像指针一样，可以通过解引用操作符得到元素的引用。
    它重载了++，--，+=，-=等操作。另外迭代器还可以用于Qt提供的一些模板函数，如qDeleteAll, qSort, qBinaryFind, qCopy等

    QMap
        使用insert向map中插入数据，也可以使用[]来插入数据(map[key] = value)，
        要注意[]有个副作用，用它访问一个不存在的key时，它会自动在map中插入一个你提供的key并生成默认的value(调用默认构造函数）。
        insert和[]一样，如果指定的key已存在，则用新的value替换原来的value
        便利QMap时我们使用迭代器。QMap的迭代器，有key()和value()两个方法，使用返回键-值对的key和value。
        也可以使用“*”操作符直接访问迭代器指向代表的value。
        QMap迭代器支持++，--，-=，+=等操做符。
*/

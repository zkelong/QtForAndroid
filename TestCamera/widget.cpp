#include "widget.h"
#include <QAndroidJniEnvironment>
#include <QAndroidJniObject>
#include <QtAndroid>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QAndroidActivityResultReceiver>
#include <QDateTime>
#include <QFile>
using namespace QtAndroid;

#define CHECK_EXCEPTION() \
    if(env->ExceptionCheck())\
    {\
        qDebug() << "exception occured";\
        env->ExceptionClear();\
    }

//   前面我讲到调用拍照的 IMAGE_CAPTURE 时，给 startActivity() 方法传递了一个 resultReceiver ，类型是 ResultReceiver 。 ResultReceiver 从 QAndroidActivityResultReceiver 继承而来，实现了 handleActivityResult 方法。
class ResultReceiver: public QAndroidActivityResultReceiver
{
public:
    ResultReceiver(QString imagePath, QLabel *view)
        : m_imagePath(imagePath), m_imageView(view)
    {

    }

    void handleActivityResult(
            int receiverRequestCode,
            int resultCode,
            const QAndroidJniObject & data)
    {
        qDebug() << "handleActivityResult, requestCode - " << receiverRequestCode
                    << " resultCode - " << resultCode
                    << " data - " << data.toString();
        //RESULT_OK == -1
        if(resultCode == -1 && receiverRequestCode == 1)
        {
            qDebug() << "captured image to - " << m_imagePath;
            qDebug() << "captured image exist - " << QFile::exists(m_imagePath);
            m_imageView->setPixmap(QPixmap(m_imagePath));
        }
    }

    QString m_imagePath;
    QLabel *m_imageView;
};

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    QHBoxLayout *actInfoLayout = new QHBoxLayout();
    layout->addLayout(actInfoLayout);
    QPushButton *getBtn = new QPushButton("Get Info");
    connect(getBtn, SIGNAL(clicked()), this, SLOT(onGetActivityInfo()));
    actInfoLayout->addWidget(getBtn);
    m_activityInfo = new QLabel();
    m_activityInfo->setWordWrap(true);
    actInfoLayout->addWidget(m_activityInfo, 1);
    layout->addSpacing(2);

    QHBoxLayout *actionLayout = new QHBoxLayout();
    layout->addLayout(actionLayout);
    m_actionEdit = new QLineEdit("android.settings.SETTINGS");
    actionLayout->addWidget(m_actionEdit, 1);
    QPushButton *launchBtn = new QPushButton("Launch");
    connect(launchBtn, SIGNAL(clicked()), this, SLOT(onLaunch()));
    actionLayout->addWidget(launchBtn);
    layout->addSpacing(2);

    QPushButton *capture = new QPushButton("CaptureImage");
    connect(capture, SIGNAL(clicked()), this, SLOT(onCapture()));
    layout->addWidget(capture);
    m_capturedImage = new QLabel();
    m_capturedImage->setScaledContents(true);
    layout->addWidget(m_capturedImage, 1);
}

Widget::~Widget()
{

}

void Widget::onLaunch() //启动活动--onLaunch() 是一个槽，点击 "Launch" 按钮会被调用，信号与槽的连接是在 Widget 的构造函数完成的。
{
    QAndroidJniObject action = QAndroidJniObject::fromString(m_actionEdit->text()); //从界面上的编辑框里获取 action 对应的字符串，对应 Android 系统的设置界面
    QAndroidJniObject intent("android/content/Intent","(Ljava/lang/String;)V", action.object<jstring>());   //这个方便的静态方法直接构造一个 JNI 对象
    startActivity(intent, 0);   ////第3行代码就比较简单了，我们不关心结果，所以只传递了第1个参数——intent，第2个参数传0，第3个参数有默认值（NULL），我们没传递。
    QAndroidJniEnvironment env; // 第 4 、5 两行代码，实际上是检查 JNI 调用是否发生了异常，如果发生异常，就清理掉异常，否则程序就会卡死在那里。
    CHECK_EXCEPTION()       //检查异常需要 QAndroidJniEnvironment 类，构造这个类的实例时，会自动关联到当前线程的 JNI 环境。然后我们就可以调用 JNIEnv 的方法 ExceptionCheck() 和 ExceptionClear() 来检查和清理异常了。因为示例中多处用到（每次 JNI 调用都需要检查异常），我定义了一个名为 CHECK_EXCEPTION 的宏：
}

/*
这里使用的QAndroidJniObject的构造函数--QAndroidJniObject(const char * className, const char * signature, ...);
第一个参数为类名，第二个参数为方法签名，第三个及以后的参数对应 Java 方法的参数。
第1个参数是 Java 中 Intent 类的全路径类名在 JNI 中的字符串表示。Intent 的全路径类名是 android.content.Intent ，对应的字符串表示为“android/content/Intent”，“.”替换为“/”。
第2个参数指定使用 Intent 构造函数中的 Intent(String action) ，这个版本的构造函数接受一个字符串形式的 action ，它的方法签名是“(Ljava/lang/String;)V”，注意构造函数没有返回值，方法签名中以 VOID 来表示。
第3个参数则是要传递给 Intent 构造函数的参数， Java 类型为 String ，我们要将第 1 行代码得到得 QAndroidJniObject 对象转换为实际的 JNI 对象（QAndroidJniObject是 Qt 对实际 JNI 对象的封装或代理），这是通过调用object()方法实现的。object()是模板方法，模版参数是 JNI 类型，这里是 jstring ，所以代码为 action.object<jstring>() 。
*/

/**
 * @brief Widget::onGetActivityInfo
 * QtAndroid名字空间有一个 androidActivity() 方法，可以获取到 Qt on Android App 使用的 Android Activity 对象。有了 Activity 对应的 JNI 对象，我们就可以通过 QAndroidJniObject 提供的方法来访问 Activity 的一些方法和属性了， onGetActivityInfo() 这个槽就是这么做的。
 */
void Widget::onGetActivityInfo()    //获取活动信息
{
    QAndroidJniEnvironment env;

    QAndroidJniObject activity = androidActivity();
    //androidActivity() 获取了一个 QAndroidJniObject 对象，代表 Android 框架里的 Activity 。 Android Activity 类有一个方法 getLocalClassName() ，可以获取 Activity 对应的 Java 类的类名。使用 JNI 得到类名的代码如下
    //使用 QAndroidJniObject 的 QAndroidJniObject	callObjectMethod(const char * methodName) const 方法，这个方法是模板方法，模板参数对应 Java 方法的返回值类型。Android Activity 的 getLocalClassName() 返回的是 String ，JNI 类型为 jstring ，所以 C++ 代码就写成上面的样子
    QAndroidJniObject className =
            activity.callObjectMethod<jstring>("getLocalClassName");
    CHECK_EXCEPTION()
    QString name = className.toString();
    // QAndroidJniObject 的 toString() 方法，它可以生成一个 JNI 对象的字符串描述，对于类型为 String（jstring） 的 JNI 对象，返回的就是字符串本身的值，这也是一种方便的、将jstring转换为 QString 的方式；对于非 String（jstring）类型的 JNI 对象，toString() 会调用对应 Java 类的 toString() 方法，返回的具体是什么字符串，就看 Java 类怎么实现 toString() 了，比如 Java 的 File 类，toString() 就会返回文件名（也可能带路径）
    int index = name.lastIndexOf('.');
    if(index != -1)
    {
        name = name.mid(index + 1);
    }
// 要调用一个 Java （JNI）对象的实例方法，需要先有实例，Qt 5.3 以后，我们不用重写 QtActivity 就可以获取到 Qt App 对应的 Android Activity 实例喽，就可以直接调用这个实例的方法来获取一些信息。比如我获取 Activity 对应的 taskId ，就使用 QAndroidJniObject 的 callMethod() 这个模版方法
    jint taskId = activity.callMethod<jint>("getTaskId");
    CHECK_EXCEPTION()
            //为了演示 QAndroidJniObject 的静态方法 T	 callStaticMethod(const char * className, const char * methodName) ，我专门看了下 android.app.Activity 的 API ，返现 getInstanceCount() 方法符合要求，于是就在 onGetActivityInfo() 槽里加入了相关代码
    jlong instanceCount = QAndroidJniObject::callStaticMethod<jlong>(
                "android/app/Activity",
                "getInstanceCount"
                );
    CHECK_EXCEPTION()

    QString activityInfo = QString("%1,task-%2,inst-%3")
            .arg(name).arg(taskId).arg(instanceCount);

    m_activityInfo->setText(activityInfo);
    m_activityInfo->adjustSize();
}

void Widget::onCapture()    //调用 Android 拍照功能
{
    QAndroidJniEnvironment env;

    // Android 上使用相机捕捉图片的事儿。要捕获图片，需要调用 android.media.action.IMAGE_CAPTURE ，在调用 IMAGE_CAPTURE 时，还可以给它传递一个 EXTRA_OUTPUT 来指定图片的存储位置。IMAGE_CAPTURE 会打开相机来拍照，并且根据操作结果设置 Activity 的 result 。当你返回键，或者拍照完成后点击拍照界面上的取消按钮时，result code 被设置为 RESULT_FAILED ，当你点击完成按钮时，拍到的图片会被保存到指定的位置并且 result code 被设置为 RESULT_OK 。
    //我在 onCapture() 里，就是根据 IMAGE_CAPTURE 的这种行为来写 JNI 调用代码。
    //constuct Intent for IMAGE_CAPTURE
    QAndroidJniObject action = QAndroidJniObject::fromString(
                "android.media.action.IMAGE_CAPTURE");
    QAndroidJniObject intent("android/content/Intent",
                             "(Ljava/lang/String;)V",
                             action.object<jstring>());

    //构造保存路径
    //setup saved image location
    QString date = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");
    QAndroidJniObject fileName = QAndroidJniObject::fromString(date + ".jpg");
    QAndroidJniObject savedDir = QAndroidJniObject::callStaticObjectMethod(
                "android/os/Environment",
                "getExternalStorageDirectory",  // 代码中先根据当前日期设置图片文件名，然后通过 QAndroidJniObject::callStaticObjectMethod() 调用 Android android.os.Environment 类的 getExternalStorageDirectory() 方法来获取外部存储的目录。 getExternalStorageDirectory() 没有参数，返回值为 Java String 对象，所以其方法签名为 “()Ljava/io/File;” 。
                "()Ljava/io/File;"
                );
    CHECK_EXCEPTION()
    qDebug() << "savedDir - " << savedDir.toString();
    QAndroidJniObject savedImageFile(
                "java/io/File",
                "(Ljava/io/File;Ljava/lang/String;)V",
                savedDir.object<jobject>(),
                fileName.object<jstring>());
    CHECK_EXCEPTION()
    qDebug() << "savedImageFile - " << savedImageFile.toString();
    QAndroidJniObject savedImageUri =
            QAndroidJniObject::callStaticObjectMethod(
                "android/net/Uri",
                "fromFile",
                "(Ljava/io/File;)Landroid/net/Uri;",
                savedImageFile.object<jobject>());
    CHECK_EXCEPTION()

    //tell IMAGE_CAPTURE the output location
    QAndroidJniObject mediaStoreExtraOutput
            = QAndroidJniObject::getStaticObjectField(
                "android/provider/MediaStore",
                "EXTRA_OUTPUT",
                "Ljava/lang/String;");
    CHECK_EXCEPTION()
    qDebug() << "MediaStore.EXTRA_OUTPUT - " << mediaStoreExtraOutput.toString();
    intent.callObjectMethod(
                "putExtra",
                "(Ljava/lang/String;Landroid/os/Parcelable;)Landroid/content/Intent;",
                mediaStoreExtraOutput.object<jstring>(),
                savedImageUri.object<jobject>());

    //我创建了一个 QAndroidActivityResultReceiver 对象，传递给 startActivity ，同时也指定 requestCode 为 1
    //launch activity for result
    ResultReceiver *resultReceiver =    //处理返回结果
            new ResultReceiver(savedImageFile.toString(), m_capturedImage);
    startActivity(intent, 1, resultReceiver);
    CHECK_EXCEPTION()
}

//在 Android 上，/data 分区被视为内部存储，应用一般会被安装到 /data/data 目录下，而外部存储实际上又分为两部分，内置 SD 分区和扩展 SD 分区。内置 SD 分区是从 FLASH 中划分出的一块存储区域，一般挂载到 /mnt/sdcard 目录下。扩展 SD 分区，则是你手机上插入的 microSD 之类的存储卡所对应的分区。因为现在很多 Android 系统都会从 FLASH 上划分一块作为内置 SD 使用，所以 Environment 类的 getExternalStorageDirectory() 方法获取到的，一般是内置 SD 分区，不是 microSD 这类外部存储卡对应的分区。
//在 Java 里，目录、文件都通过 java.io.File 类来表示。我们获取到的外部存储目录，也是一个 File 对象。 File 类有一个构造函数 File(File dir, String fileName) ，可以创建一个 File 对象，代表 dir 对象所指定的目录下的 fileName 文件。 File 对象的 toString() 方法会返回它所代表的文件的路径。
/*
代码里的 savedImageFile 对象，使用 “(Ljava/io/File;Ljava/lang/String;)V”作为 File 类构造函数的签名，然后用 savedDir.object<jobject>() 获得外部存储目录对应的 JNI 对象来传递给构造函数。
//在我们通过 Intent 调用 IMAGE_CAPTURE 时，要指定的存储位置，是通过 android.net.Uri 类表示的，因此我又调用 Uri 的静态方法 fromFile() 创建了一个 Uri 对象，fromFile()只有一个类型为 File 的入参，返回值则是 Uri ，因此方法签名为“(Ljava/io/File;)Landroid/net/Uri;”。

也许你注意到在使用 QAndroidJniObject 的 callStaticObjectMethod() 方法，给 Java 类传参时，多次用到 xxx.object<jobject>() 这种调用。还记得之前我们将 QAndroidJniObject 转为 jstring 的代码是 xxx.object<jstring> ，那转换代表 JNI File 对象的 QAndroidJniObject 对象时为何不使用 xxx.object<jfile>() 呢？这是因为，在 JNI 的类型系统里，Java String 作为基础类型，而其它的对象类型，统一都使用 jobject 来表示。因此以后我们不管拿到什么样的 QAndroidJniObject 对象，只要是代表一个非 String 类型的 Java 对象，想转换为实际的 JNI 对象，都用 xxx.object<jobject>() 这种方式。我们得到的 Uri 对象，在传递给 Intent 时就是这么用的。

Android Intent 类提供了一系列的 putExtra 方法，让我们能够把类型为 int 、 float 、 String 、int[] 、double 、char 、 byte 等等的数据存储在 Intent 实例中，带给被调用方。被调用方可以用 getExtra 方法获取到发起调用一方传递的数据。这就是使用 Intent 传递数据的一般用法。 Intent 还有一个 putExtras方法，可以传递一个复杂数据对象——Bundle，如果你要传递的数据很多，就可以把数据组合为一个 Bundle 。

    要在两个组件之间传递数据，就要有个约定，因为传递的数据可能不知一个，就需要给每个数据起个名字，这就是 key ，putExtra() 方法的第一个参数类型为字符串，用于指定数据的 key ，接收 Intent 的一方可以根据这个 key 把数据取出来。
对于 IMAGE_CAPTURE ，它接受的数据是 Uri ，对应的 key 则为 android.provider.MediaStore.EXTRA_OUTPUT ，是 MediaStore 类的静态成员变量。因为我在代码里就先调用 QAndroidJniObject::getStaticObjectField() 方法获取到 EXTRA_OUTPUT 。这里又得岔开来讲一个喽。

    QAndroidJniObject 不但提供了调用 Java 方法的接口，还提供了访问和修改 Java 属性的接口。 getStaticObjectField 这一系列的重载方法，就是访问 Java 类的静态成员变量的；而 getObjectField 那一系列的重载方法，则是访问 Java 类的实例成员变量（这种成员变量，每个实例都有一份）的。

    在访问 Java 类成员变量时，需要变量名字和变量签名。比如获得 EXTRA_OUTPUT 的代码，传递的 fieldName 为 “EXTRA_OUTPUT” ，传递的签名为 “Ljava/lang/String;” ，表示 EXTRA_OUTPUT 是一个类型为 String 的静态成员。

    得到了 EXTRA_OUTPUT ，调用 Intent 的 putExtra 就可能把 savedImageUri 存入 Intent （关联的key为 EXTRA_OUTPUT）。我调用的 putExtra 方法原型为：
Android 提供了一个轻量级、高效率的进程间通信机制： Parcel 。使用 Parcel 通信时，交互的数据需要序列化，因此 Android 设计了 Parcelable 接口，方便传递数据。你想传递的数据，只要实现 Parcelable 接口和特定的模板方法即可。我们用到的 Uri ，就是 Parcelable 的子类。也因此我选择了上面的 putExtra() 方法。
//如果你想传递更复杂的数据，可以通过 Intent ，也就是说了，被调用的 Activity ，也可以传递一个 Intent 给调用那一方。你看，Android Activity 的 onActivityResult() 方法原型如下：
void onActivityResult(int requestCode, int resultCode, Intent data);


这与我们的 handleActivityResult 方法是对应的，第三个参数，类型就是 Intent 。

当你这么做的时候，通常需要写 Java 代码来实现能使用 Intent 传递数据的组件，你可以通过下面的方法把 Intent 传递给调用那方：

[cpp] view plain copy

void setResult(int resultCode, Intent data);
*/

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

void Widget::onLaunch()
{
    QAndroidJniObject action = QAndroidJniObject::fromString(m_actionEdit->text());
    QAndroidJniObject intent("android/content/Intent","(Ljava/lang/String;)V", action.object<jstring>());
    startActivity(intent, 0);
    QAndroidJniEnvironment env;
    CHECK_EXCEPTION()
}

void Widget::onGetActivityInfo()
{
    QAndroidJniEnvironment env;

    QAndroidJniObject activity = androidActivity();
    QAndroidJniObject className =
            activity.callObjectMethod<jstring>("getLocalClassName");
    CHECK_EXCEPTION()
    QString name = className.toString();
    int index = name.lastIndexOf('.');
    if(index != -1)
    {
        name = name.mid(index + 1);
    }

    jint taskId = activity.callMethod<jint>("getTaskId");
    CHECK_EXCEPTION()
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

    QAndroidJniObject action = QAndroidJniObject::fromString(
                "android.media.action.IMAGE_CAPTURE");
    QAndroidJniObject intent("android/content/Intent",
                             "(Ljava/lang/String;)V",
                             action.object<jstring>());

    //setup saved image location
    QString date = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");
    QAndroidJniObject fileName = QAndroidJniObject::fromString(date + ".jpg");
    QAndroidJniObject savedDir = QAndroidJniObject::callStaticObjectMethod(
                "android/os/Environment",
                "getExternalStorageDirectory",
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

    ResultReceiver *resultReceiver =
            new ResultReceiver(savedImageFile.toString(), m_capturedImage);
    startActivity(intent, 1, resultReceiver);
    CHECK_EXCEPTION()
}

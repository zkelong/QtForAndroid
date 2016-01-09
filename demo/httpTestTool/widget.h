#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QGroupBox>
#include <QComboBox>
#include <QCheckBox>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QProgressBar>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

protected slots:
    void onAddHttpHeaderValue();
    void onStart();
    void onMethodChanged(const QString &method);
    void onMetaDataChanged();
    void onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void onUploadProgress(qint64 bytesSent, qint64 bytesTotal);
    void onReadyRead();
    void onFinished();

protected:
    void setupGUI();
    void disableControls();
    void enableControls();

private:
    QString requestString(QNetworkRequest *req);
    QString responseString(QNetworkReply *reply);
    void resetState();
    bool openFile(bool save, QString &errorString);

protected:
    QGroupBox * m_headerValueGroup;
    QLabel * m_headerKeyLabel;
    QLineEdit * m_headerKeyEdit;
    QLabel * m_headerValueLabel;
    QLineEdit * m_headerValueEdit;
    QPushButton * m_addHttpHeaderValueButton;

    QGroupBox * m_stateGroup;
    QTextEdit * m_stateText;
    QProgressBar * m_progress;

    QGroupBox * m_paramGroup;
    QLabel * m_urlLabel;
    QLineEdit * m_urlEdit;
    QLabel * m_methodLabel;
    QComboBox * m_methodCombo;
    QPushButton * m_startButton;

    QNetworkAccessManager m_nam;
    QNetworkReply * m_reply;
    QNetworkRequest * m_request;
    QString m_strFilePath;
    QFile * m_file;
};

#endif // WIDGET_H

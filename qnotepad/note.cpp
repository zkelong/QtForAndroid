#include "note.h"
#include <QTextStream>
#include <QFile>
#include <QDir>
#include <QDebug>

void QNote::loadNotes(QList<QNote *> &notes)
{
    QFile file(QString("%1/qnote.txt").arg(QDir::currentPath()));   //QString用法，有参数%1/
    if(!file.open(QIODevice::ReadOnly)) //只读打开失败
    {
        qDebug() << "can't open qnote.txt for read - " << file.errorString();
        return;
    }
    QTextStream textStream(&file);  //操作文件
    textStream.setAutoDetectUnicode(true);  //如果文件编码为UTF-16或UTF-32，文件编码转换为UTF
    QString line;       //读取的每一行文字
    QString title;      //标题
    QString content;    //内容
    QNote *note;
    while(!textStream.atEnd())  //未读到结尾
    {
        line = textStream.readLine();       //一行一行读，一行是多少？默认不限长度？回车隔开行，而readLine不返回回车。
        if(line.startsWith(NEW_NOTE_PREFIX))    //新笔记标签，多个笔记放一个文件
        {
            if(!title.isEmpty() && !content.isEmpty())
            {
                note = new QNote(title.trimmed(), content); //新建一个笔记来装
                notes.append(note);
            }
            title.clear();      //清空字符串
            content.clear();
            title = line.mid( NEW_NOTE_PREFIX_LEN );    //截取字符串
            continue;
        }
        content += line;
        content += '\n';
    }
    if(!title.isEmpty() && !content.isEmpty())
    {
        note = new QNote(title.trimmed(), content);
        notes.append(note);
    }

    file.close();
}

void QNote::saveNotes(QList<QNote *> &notes)
{
    QFile file(QString("%1/qnote.txt").arg(QDir::currentPath()));
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        qDebug() << "can't open qnote.txt for write - " << file.errorString();
        return;
    }
    QTextStream textStream(&file);
    textStream.setCodec("utf-8");
    int count = notes.size();
    QNote *note;
    for(int i = 0 ; i < count; i++)
    {
        note = notes.at(i);
        textStream << NEW_NOTE_PREFIX << note->m_strTitle << "\n";
        textStream << note->m_strContent << "\n";
    }
    file.close();
}

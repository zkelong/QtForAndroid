#ifndef NOTE_H
#define NOTE_H

#include <QString>
#include <QList>

#define NEW_NOTE_PREFIX "##NEW-NOTE "
#define NEW_NOTE_PREFIX_LEN  11

class QNote{
public:
    /**构造函数
     * @param title 笔记标题
     * @param content 笔记内容
     */
    QNote(const QString &title, const QString &content)
        : m_strTitle(title), m_strContent(content)
    {
    }

    /**构造函数
     */
    QNote(const QNote &n)
        : m_strTitle(n.m_strTitle)
        , m_strContent(n.m_strContent)
    {

    }

    QNote &operator=(const QNote &r)
    {
        if(this != &r)
        {
            m_strTitle = r.m_strTitle;
            m_strContent = r.m_strContent;
        }
        return *this;
    }

    static void loadNotes(QList<QNote*> & notes);   //加载
    static void saveNotes(QList<QNote*> & notes);   //保存

    QString m_strTitle;
    QString m_strContent;
};

#endif // NOTE_H

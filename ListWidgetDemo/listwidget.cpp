#include "listwidget.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

FileExplorer::FileExplorer(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *modeLayout = new QHBoxLayout();
    mainLayout->addLayout(modeLayout);

    QLabel *label = new QLabel();
    modeLayout->addWidget(label, 1);
    m_modeCombo = new QComboBox();
    m_modeCombo->addItem("List");
    m_modeCombo->addItem("Icon");
    connect(m_modeCombo, SIGNAL(currentTextChanged(QString))
            ,this, SLOT(onViewModeChanged(QString)));
    modeLayout->addWidget(m_modeCombo);
    m_list = new QListWidget();
    connect(m_list, SIGNAL(currentTextChanged(QString)),
            label, SLOT(setText(QString)));

    //给添加数据
    QListWidgetItem *item = new QListWidgetItem(
                QIcon(":/folder"), "folder");
    item->setTextColor(Qt::blue);
    m_list->addItem(item);
    item = new QListWidgetItem(
                QIcon(":/images/videoFile.png"), "one.mp4");
    m_list->addItem(item);
    item = new QListWidgetItem(
                QIcon(":/images/audioFile.png"), "love.mp3");
    m_list->addItem(item);
    m_list->addItem(new QListWidgetItem(
                        QIcon(":/images/imageFile.png"), "love.mp3"));
    m_list->addItem("text file.txt");
    mainLayout->addWidget(m_list, 1);
    m_list->setSelectionMode(QAbstractItemView::SingleSelection);
    m_list->setSpacing(6);
    m_list->setCurrentRow(0);
}

void FileExplorer::onViewModeChanged(const QString &mode)
{
    m_list->setViewMode( mode == "List" ?
                             QListView::ListMode :
                             QListView::IconMode );
}

/*QListWidget的创建与其他普通Qt Widget一样，只需要使用new操作符分配一个对象即可。
 如果将它作为子控件，可以指定一个父，获知交给布局管理器即可。

 QListWidget
    addItem、addItems、insertItem、insertItems...

 QListWidgetItem
    icon、setIcon、text、setText、data、setData
*/

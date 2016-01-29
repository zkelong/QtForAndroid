#include "tablewidget.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QMessageBox>
#include <QStringList>
#include <QIntValidator>

ProgramSkillWidget::ProgramSkillWidget(QWidget *parent)
    : QWidget(parent)
{
    m_skills.append(new ProgramSkill("C++", "3+项目为熟练"));
    m_skills.append(new ProgramSkill("Qt", "3+项目为熟练"));
    m_skills.append(new ProgramSkill("Android", "3+项目为熟练"));
    m_skills.append(new ProgramSkill("Java", "3+项目为熟练"));
    m_skills.append(new ProgramSkill("Multimedia","2+视频项目为熟练"));

    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *label = new QLabel("Please evaluate your program skills.");
    layout->addWidget(label);
    m_skillTable = new QTableWidget(m_skills.size(), 4);
    layout->addWidget(m_skillTable, 1);
    m_submitButton = new QPushButton("submit");
    connect(m_submitButton, SIGNAL(clicked()),
            this, SLOT(onSubmit()));
    layout->addWidget(m_submitButton, 0,
                      Qt::AlignVCenter | Qt::AlignRight);
    setupProgramSkillTable();
}

ProgramSkillWidget::~ProgramSkillWidget()
{

}

void ProgramSkillWidget::onCellClicked(int row, int column)
{
    if(column == 0)
    {
        QComboBox *combo = m_levels.at(row);
        QLineEdit *edit = m_years.at(row);
        combo->setEnabled(!combo->isEnabled());
        edit->setEnabled(!edit->isEnabled());
    }
}

void ProgramSkillWidget::onLevelChanged(const QString &text)
{
    QComboBox * levelCombo = qobject_cast<QComboBox*>(sender());
    if(levelCombo)
    {
        int index = m_levels.indexOf(levelCombo);
        if(index >= 0 ) m_skills.at(index)->m_level = text;
    }
}

void ProgramSkillWidget::onYearsChanged(const QString &text)
{
    QLineEdit * yearEdit = qobject_cast<QLineEdit*>(sender());
    if(yearEdit)
    {
        int index = m_years.indexOf(yearEdit);
        if(index >= 0 ) m_skills.at(index)->m_nUseYear = text.toInt();
    }
}

void ProgramSkillWidget::onSubmit()
{
    QMessageBox::information(this, "evaluation"
                             , evaluate(), QMessageBox::Ok);
}

QString ProgramSkillWidget::evaluate()
{
    int count = m_skills.size();
    ProgramSkill *skill;
    int familiars = 0;
    int years3s = 0;
    int masters = 0;
    for(int i = 0; i < count; i++)
    {
        skill = m_skills.at(i);
        if(skill->m_nUseYear >= 3) years3s++;
        if(skill->m_level == "熟练") familiars++;
        else if(skill->m_level == "精通")
        {
            masters++;
            familiars++;
        }
    }
    if(masters >= 2 && years3s >= 3)
    {
        return "A Senior Programmer!";
    }
    else if(familiars >= 2 && years3s >= 2)
    {
        return "Good gay, go on please";
    }
    else if(masters + familiars < 2)
    {
        return "A Poor Programmable Monkey...";
    }

    return "Strange thing ...";
}

void ProgramSkillWidget::setupProgramSkillTable()
{
    connect(m_skillTable, SIGNAL(cellClicked(int,int)),
            this, SLOT(onCellClicked(int,int)));
    m_skillTable->setEditTriggers(QTableWidget::NoEditTriggers);
    QStringList headers("Skill");
    headers << "Description" << "Level" << "Year <40";
    m_skillTable->setHorizontalHeaderLabels(headers); //水平方向的表格表头；setHorzontalHeaderItem()垂直表头
    int count = m_skills.size();
    ProgramSkill *skill;
    QComboBox *levelCombo;
    QLineEdit *yearEdit;
    QIntValidator *validator;
    m_skillTable->setColumnWidth(0, 130);  //设置宽度
    m_skillTable->setColumnWidth(1, 200);
    m_skillTable->setColumnWidth(2, 150);
    m_skillTable->setColumnWidth(3,100);
    for(int i = 0; i < count; i++)
    {
        m_skillTable->setRowHeight(i, 50);
        skill =  m_skills.at(i);
        m_skillTable->setItem(i, 0, new QTableWidgetItem(skill->m_name));
        m_skillTable->setItem(i, 1, new QTableWidgetItem(skill->m_description));
        levelCombo = new QComboBox();
        m_levels.append(levelCombo);
        connect(levelCombo, SIGNAL(currentTextChanged(QString)),
                this, SLOT(onLevelChanged(QString)));
        levelCombo->addItem("听说");
        levelCombo->addItem("用过");
        levelCombo->addItem("熟练");
        levelCombo->addItem("精通");
        levelCombo->setEditable(false);  //禁止编辑
        levelCombo->setCurrentIndex(0);
        m_skillTable->setCellWidget(i, 2, levelCombo);
        yearEdit = new QLineEdit("0");
        m_years.append(yearEdit);
        connect(yearEdit, SIGNAL(textChanged(QString)),
                this, SLOT(onYearsChanged(QString)));
        validator = new QIntValidator(0, 40, yearEdit);
        yearEdit->setValidator(validator);
        m_skillTable->setCellWidget(i, 3, yearEdit);
    }
}

/***
1.设置表格行列选择模式
    整行：m_skillTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    单元格：SelectItems
    列：SelectColumns
2.单选与多选
    setSelectionBehavior()
    不可选： QAbstractItem::NoSelection
    单选：SingleSelection
    多选：MultiSelection
    与shift键结合连续选择：ContiguoousSelection
    与ctrl键结合进行多选：ExtendedSeleciton
3.表头及单元格的文字颜色
    每个格子其实也是QTableWidgetItem，horizontalHeaderItem()获取到表头对应的对象后，就可以用QTableWidgetItem类方法来设置字体、颜色、前景色、背景色等。
4.合并（扩展单元格）
    QTableView的setSpan(int row, int column,, int rowSpanCount, int columnSpanCount)方法可合并单元格。
    前两个参数指定要扩展的单元格的位置，后两个参数指定要扩展的行数和列数。
    如setSpan(0, 0, 2, 2)则会使得表格左上角第一个单元格合并包围的那3个单元格
5.获取单元格内容
    可以使用item(int row, int column)方法获取指定行列位置的单元格对应的QTableWidgetItem对象。
    QTableWidget还有itemClicked(QTableWidgetItem *item)信号，可以直接获取代表一个单元格的QTableWidgetItem对象。
    QTabWidget所有以item为前缀的信号，都可以直接获取QTableWidgetItem.
*/

/*Qt GUI编程
	GUI组件：
		QWidget, QLabel, QPushButton, QComboBox, QMessageBox
	1.QRadioButton
		单选按钮，通常和QGroupBox或QButtonGroup一起使用。
		toggled信号：获知每个单选按钮的状态变化。
	2.QCheckBox
		复选按钮，一组选项中选一个或多个。
		可以通过setExclusive(bool)方法达到互斥使用复选框的目的。
		信号：stateChanged()
		检查选中状态：isChecked()
	3.QGroupBox
		分组框，将其他窗口部件组合在一起显示。
		本身也支持选择，setCheckable()设置。设置了后，标题栏会出现一个复选框，当它选中了，子控件才可选择。
		标题：setTitle()，对齐方式：Qt::AlignLeft, Qt::AlignRight, Qt::alignHCenter
		需要一个布局管理器来管理它的子控件的布局，可以使用各种布局管理器，如：QVBoxLayout，QHBoxLayout，QGridLayout
		例子：QGroupBox
	4.QLineEdit
		单行文本编辑框。
		可输入编辑纯文本，支持拷贝、粘贴、撤销、重做、拖放等功能。
		回显模式：setEchoMode(), QLineEdit::Normal(默认，输入啥显示啥), QLineEdit::Password, QLineEdit::PasswordEchoOnedit(输入时显示输入内容，不编辑是显示掩码)
		改变文本：setText(), insert(); 获取文本：text()
		信号：textChanged(),  editingFinished()--按下Return或Enter键, returnPressed(), selectionChanged()--选择编辑框内文本变化
		只输入数字：setInputMask(), setValidator() 例：正则表达式控制只能输入IPv4地址的代码片段
			QRegExp rx("2[0-5]{2}|2[0-4][0-9]|1?[0-9]{1,2})"
					 "\\.2[0-5]{2}|2[0-4][0-9]|1?[0-9]{1,2})"
					 "\\.2[0-5]{2}|2[0-4][0-9]|1?[0-9]{1,2})"
					 "\\.2[0-5]{2}|2[0-4][0-9]|1?[0-9]{1,2})");
			ipEidt->setValidator(new QRegExpValidator(rx));
	5.QTextEdit
		文本编辑框，所见即所得（WYSIWYG）的文本编辑器。
		支持HTML风格标签
		可用于显示或编辑纯文本和富文本，能显示文字、图片、列表、表格等元素。
		能够支持字数很多的大文本，能够快速处理用户输入。
		能正确处理段落和字符，以字为边界断行，自动适应窗口的宽度。一个段落中的每个字和字符，都可以有自己的字体、颜色等属性。每个段落还可以有自己的对齐属性。
		可以把QTextEdit作为一个文本显示控件使用，通过setPlainText(), setText()或setHtml()提供文本给它显示
		也可以作为一个功能丰富的文本编辑器来使用，可以使用setFontItalic(), setFontWeight(), setFontFamily(), setFontUnderline(),setFontPoinSize(), setTextColor(), setCurrentFont()等来改变文本的显示属性。
		段落对其方式：setAlignMent()
		按键绑定：Ctrl+c，Ctrl+V，HOME等。
		用QTextDocument来保存格式化文本
		可通过QTextCursor来编辑QTextEdit背后的文档对象
		可以使用QTextFormat及其各种派生类（如QTextBlockFormat、QTextCharFormat、QTextFrameFormat、QTextListFormat，可以定制）来调整文档的格式
		可用QSyntaxHightlinghter来处理文字语法高亮状态。
		例子：qnote
		索引：Rich Text Processing
	6.QTabWidget
		选项卡控件。
		一般与选项栏（QTabBar）一起使用，QTabBar可以通过addTab(), insertTab()等方法加入。
		使用QTabWidget的一般步骤：
			a.创建一个QTabWidget对象
			b.为每一个选项创建一个QWidget实例，别指定它的父
			c.向页面widget中加入各种子控件，使用布局管理器管理它们。
			d.使用addTab()或insert()把每个界面都加入到QTabWidget, 并为它们指定一个合适的标签以及一个可选的键盘快捷键。
		当用户选择一个选项标签时，QTabWidget会发射currentChanged()信号。当前选项可以通过currentIndex()和currentWidget()获知
		也可以使用setCurrentIndex()和setCurrentWidget()来设置它们。
	7.QListWidget
		QListView是Qt的Model/View framework中提供的Model/View类库中的一个
		QListWidget是QListView的派生类，提供一个经典的基于item的列表组件，使用基于item的接口来添加、删除、维护元素。
		例子：listwidgetdemo
	8.Qt资源文件系统
		Qt通过一个qrc文件夹管理图片资源和其他资源。这个文件既可以通过新建向导添加，也可以直接编辑pro文件通过RESOURCES变量加入：
			RESOURCE += \
				listWidgetDemo.qrc
		qrc文件是一个xml文件，你可以手动编辑它，或者使用Qt Creator提供的图形化编辑器来插入资源。
		代码中，如果使用资源文件时，是以“:/”开始的，后边借的路径类似Linux下的路径。
		例:
			":/images/folder.png"
			"qrc:///images/folder.png"
		资源的别名机制，允许你为实际的资源文件起一个其他名字，多数时候是为了编程引用方便。
			":/folder"   //对应xml文件：<file alias="folder">images/folder.png</file>
	9.QTableWidget
		和QListWidget一样，QTableWidget是Qt框架提供另外一个以方便开发者为目的地类，它继承自QTableView，内部实现了一个默认的Model和Delegate，内部实现了一个默认的Model和Delegate。
		向开发者暴露基于item的接口。
		类似Excel，表格形式显示数据。
		demo: ProgramSkillSurvey
			
		
**/
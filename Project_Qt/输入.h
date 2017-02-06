#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QMap>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>

class AddressBook: public QWidget
{
	public:
	Q_OBJECT
//报错不能用
	public:
	AddressBook(QWidget *);
	~AddressBook( ){}
	private:
	//输入框
	QLineEdit *nameLine;
	QTextEdit *addressText;
	//输入label不用声明
	
	//需要一个存储容器，存储联系人，使用QMap类
	QMap<QString,QString>contact;
	QString oldName;
	QString oldAddress;
	
		
	//现在添加按钮
	QPushButton *addButton;
	QPushButton *submitButton;
	QPushButton *cancelButton;
	
	//对应的三个槽
	public slots:
	void addContact();
	void submitContact();
	void cancelContact();
};

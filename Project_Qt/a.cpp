#include "输入.h"
AddressBook::AddressBook(QWidget *parent):QWidget(parent)
{
	QLabel*nameLabel=new QLabel("姓名：");
	nameLine=new QLineEdit;
	nameLine->setReadOnly(true);//设为只读，点击添加按钮方可输入
	QLabel*textLabel=new QLabel("地址：");
	addressText=new QTextEdit;
	addressText->setReadOnly(true);//上同
	
	
	//示例化按钮
	addButton=new QPushButton("添加");
	addButton->show();
	submitButton=new QPushButton("保存");
	submitButton->hide();            //隐藏按钮
	cancelButton=new QPushButton("撤销");
	cancelButton->hide();
	//关联对应槽
	QObject::connect(addButton,SIGNAL(clicked()),this,SLOT(addContact()));
	QObject::connect(submitButton,SIGNAL(clicked()),this,SLOT(submitContact()));
	QObject::connect(cancelButton,SIGNAL(clicked()),this,SLOT(cancelContact()));
	
	
	//排列按钮布局
	QVBoxLayout*buttonLayout1=new QVBoxLayout;
	buttonLayout1->addWidget(addButton,Qt::AlignTop);
	//Qt::AlignTop使textLabel居上，没有则居中
	buttonLayout1->addWidget(submitButton);
	buttonLayout1->addWidget(cancelButton);
	buttonLayout1->addStretch();
	
	
	QGridLayout*mainLayout=new QGridLayout;
	mainLayout->addWidget(nameLine,0,1);
	mainLayout->addWidget(nameLabel,0,0);
	mainLayout->addWidget(textLabel,1,0,Qt::AlignTop);
	mainLayout->addWidget(addressText,1,1);
	mainLayout->addLayout(buttonLayout1,1,2);
	
	
	setLayout(mainLayout);
	setWindowTitle("addressbook");
}

//添加按钮的操作
void AddressBook::addContact()
{
	oldName=nameLine->text();
	oldAddress=addressText->toPlainText();
	
	nameLine->clear();
	addressText->clear();
	
	nameLine->setReadOnly(false);
	nameLine->setFocus(Qt::OtherFocusReason);
	addressText->setReadOnly(false);
	
	addButton->setEnabled(false);
	submitButton->show();
	cancelButton->show();
}

//保存按钮的操作
void AddressBook::submitContact()
{
	QString name=nameLine->text();
	QString address=addressText->toPlainText();
	
	if(name==""||address=="")
	{
		QMessageBox::information(this,"输入为空!","输入非空姓名和地址");
		return ;
	}
	if (!contact.contains(name))
	{
		contact.insert(name,address);
		QMessageBox::information(this,"添加成功!",QObject::tr("\"%1\"已添加到地址簿。").arg(name));
	}
	else
	{
		QMessageBox::information(this,"添加出错!",QObject::tr("\"%1\"已经添加过了!").arg(name));
		return ;
	}
	if (contact.isEmpty())
	{
		nameLine->clear();
		addressText->clear();
	}
		
		
	nameLine->setReadOnly(true);
	addressText->setReadOnly(true);
	addButton->setEnabled(true);
	submitButton->hide();
	cancelButton->hide();
}

//撤销按钮的操作
void AddressBook::cancelContact()
{
	nameLine->setText(oldName);
	nameLine->setReadOnly(true);
	addressText->setText(oldAddress);
	addressText->setReadOnly(true);
	
	addButton->setEnabled(true);
	submitButton->hide();
	cancelButton->hide();
}

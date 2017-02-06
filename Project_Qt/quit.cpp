#pragma execution_character_set("utf-8")
#include <QApplication>
#include <QPushButton>
int main(int argc,char*argv[])
{
	QApplication app(argc,argv);
	QPushButton *button=new QPushButton("退出");
	QObject::connect(button,SIGNAL(clicked()),&app,SLOT(quit()));
	button->resize(10,20);
	button->show();
	return app.exec();
}
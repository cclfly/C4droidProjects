#include <QApplication>
#include <QPushButton>
//#include <QWebview>

int main(int argc,char*argv[])
{
	QApplication app(argc,argv);
	//QWebview web;
	//web.show();
	QPushButton btn;
	btn.setText(QString(qVersion()));
	btn.show();
	app.exec();
}
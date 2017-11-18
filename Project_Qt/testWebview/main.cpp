#include <QApplication>
#include <QWebview>

int main(int argc,char*argv[])
{
	QApplication app(argc,argv);
	QWebview web;
	web.show();
	app.exec();
}
#include <QApplication>
#include <QListWidget>

int main(int argc,char*argv[])
{
	QApplication app(argc,argv);
	QStringList list=QApplication::arguments();
	QListWidget listWidget;
	listWidget.addItems(list);
	listWidget.show();
	return app.exec();
}
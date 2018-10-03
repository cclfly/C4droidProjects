#include <QApplication>
#include <QClipboard>
#include <QListWidget>

int main(int argc, char *argv[])
{
	QApplication app(argc,argv);
	QListWidget *list = new QListWidget;
	QClipboard *clip = QApplication::clipboard();
	QApplication::connect(clip, &QClipboard::dataChanged, [list,clip](){list->addItem(new QListWidgetItem(clip->text()));});
	list->show();
	app.exec();
}
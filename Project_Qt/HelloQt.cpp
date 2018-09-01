/*c4droid代码手册
 *hello world
 *TTHH编写
 *转载请说明出处
*/
#include <QApplication>
#include <QtGui>
#include <QDialog>
#include <QLabel>
#include <QDesktopWidget>
#include <QRect>

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	QDialog* dd=new QDialog();
	QLabel* label=new QLabel(dd);
	label->setText("hello Qt");
	QRect rect=QDesktopWidget().screenGeometry();
	dd->setGeometry((rect.width()-200)/2,(rect.height()-100)/2,200,100);
	dd->show();
	return app.exec();
}
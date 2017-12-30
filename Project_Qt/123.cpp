#include <QApplication>
#include <QDesktopWidget>
#include <QWidget>
#include <QPushButton>

int main(int argc,char*argv[])
{
	QApplication app(argc,argv);
	int width=QApplication::desktop()->width();
	int height=QApplication::desktop()->height();
	
	QWidget w(0);
	QPushButton b(&w);
	b.setText("exit");
	b.setGeometry((width-200)/2,(height-80-80)/2,200,80);
	QWidget::connect(&b,&QPushButton::clicked,&app,&QApplication::quit);
	
	w.show();
	return app.exec();
}
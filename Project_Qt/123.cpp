#include <QApplication>
#include <QDesktopWidget>
#include <QWidget>
#include <QPushButton>
#include <string>
#include <sstream>

using std::string;
using std::stringstream;

int main(int argc,char*argv[])
{
	QApplication app(argc,argv);
	int width=QApplication::desktop()->width();
	int height=QApplication::desktop()->height();
	/*stringstream ss;
	string str;
	ss<<wid;
	ss>>str;*/
	
	QWidget w(0);
	QPushButton b(&w);
	b.setText("exit");
	b.setGeometry((width-200)/2,(height-80-80)/2,200,80);
	QWidget::connect(&b,SIGNAL(clicked()),&app,SLOT(quit()));
	
	w.show();
	return app.exec();
}
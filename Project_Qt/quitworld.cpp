#include <QApplication>
#include <QPushButton>
#include <QBoxLayout>
int main(int argc,char **argv)
{
	QApplication app(argc,argv);
	
	QWidget *widget=new QWidget;
	
	QPushButton *hello=new QPushButton("Hello world !",widget);
	hello->setGeometry(0,0,540,470);
	QPushButton *quit=new QPushButton("Quit !",widget);
	quit->setGeometry(0,470,540,470);
	QObject::connect(quit,SIGNAL(clicked()),&app,SLOT(quit()));
	
	QVBoxLayout *qvb=new QVBoxLayout;
	qvb->addWidget(hello);
	qvb->addWidget(quit);
	
	widget->setGeometry(0,0,540,960);
	
	widget->setLayout(qvb);
	widget->show();
	
	app.exec();
}
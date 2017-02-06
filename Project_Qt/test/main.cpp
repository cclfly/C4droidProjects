#include <QApplication>
#include "GLWidget.h"
#include <QDesktopWidget>

class widget:public QWidget
{
	public:
	GLWidget* gw;
	Ui::Widget* ui;
public:
	widget(QWidget *parent=0):QWidget(parent),ui(new Ui::Widget)
	{
		gw=new GLWidget(this);
		QRect screen=QApplication::desktop()->screenGeometry();
		gw->setGeometry(0,0,screen.width(),screen.height());
		gw->show();
		ui->setupUi(this);
		connect(ui->exit_button,SIGNAL(clicked()),qApp,SLOT(quit()));
	}
};

int main(int argc,char** args)
{
    QApplication a(argc,args);
    widget gw;
    gw.show();
    
    return a.exec();
}
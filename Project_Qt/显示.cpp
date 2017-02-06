#include <QApplication>
#include <QPushButton>
#include <QWidget>

class MyWidget :public QWidget
{
//	Q_OBJECT
	public:
	MyWidget(QWidget *);
	private:
	QPushButton *back;
	//QPushButton *ok;
};

MyWidget::MyWidget(QWidget *parent=0)
:QWidget(parent)
{
/*	ok=new QPushButton("确认",this);
	ok->setMinimumSize(540,960);
	ok->setMaximumSize(540,960);
	connect(ok,SIGNAL(clicked()),back,SLOT(show()));
	ok->show();
	*/
	back=new QPushButton("返回",this);
	back->setMinimumSize(540,960);
	back->setMaximumSize(540,960);
	connect(back,SIGNAL(clicked()),this,SLOT(hide()));
}

int main(int argc,char **argv)
{
	QApplication app(argc,argv);
	MyWidget mw(0);
	mw.setGeometry(0,0,540,960);
	
	QPushButton *open=new QPushButton("打开",0);
	QObject::connect(open,SIGNAL(clicked()),&mw,SLOT(show()));
	
	open->show();
	app.exec();
}
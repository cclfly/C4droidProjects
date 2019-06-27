#include <QPushButton>
#include <QApplication>
#include <QHBoxLayout>
#include <QSlider>
#include <QSpinBox>
int main(int argc,char *argv[])
{
	QApplication app(argc,argv);
	
	QWidget *window=new QWidget;
	window->setWindowTitle("Enter your age");
	
	QSpinBox *spinBox=new QSpinBox;
	QSlider *slider=new QSlider(Qt::Horizontal);
	spinBox->setRange(0,130);
	slider->setRange(0,130);
	
	QObject::connect(spinBox,SIGNAL(valueChanged(int)),slider,SLOT(setValue(int)));
	QObject::connect(slider,SIGNAL(valueChanged(int)),spinBox,SLOT(setValue(int)));
	spinBox->setValue(35);
	
	QHBoxLayout *layout=new QHBoxLayout;
	layout->addWidget(spinBox,1);
	layout->addWidget(slider,4);
	//window->setLayout(layout);
	
	QPushButton *quit=new QPushButton("退出",0);
	//quit->setGeometry(90,76,66,99);
	//quit->resize(78,66);
	QObject::connect(quit,SIGNAL(clicked()),&app,SLOT(quit()));
	
	QVBoxLayout *qvb=new QVBoxLayout;
	qvb->addLayout(layout);
	qvb->addWidget(quit);
	
	window->setLayout(qvb);
	
	window->show();
	
	return app.exec();
}
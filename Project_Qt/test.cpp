#include <QApplication>
#include <QLabel>
class Hi:public QWidget
{
	
    Q_OBJECT;
public:
    explicit Hi(QWidget *parent = 0);
    ~Hi();
    
    QLabel *m_labelInfo;
	
};

Hi::Hi(QWidget *parent) : QWidget(parent)
{
    resize(300, 200);
    m_labelInfo = new QLabel( "<h1>Hello Widget!</h1>", this );
    //m_labelInfo->setGeometry(10, 10, 200, 40);
}

Hi::~Hi()
{
    delete m_labelInfo; 
    m_labelInfo = NULL;
}


int main (int argc,char *argv[])
{
	QApplication app(argc,argv);
	//QLabel label("毛毛用c4写这玩意太坑了");
	//label.show();
	(new Hi())->show();
	return app.exec();
}

#include "test.cpp.moc"
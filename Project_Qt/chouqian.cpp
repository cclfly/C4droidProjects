#include <QLCDNumber>
#include <QApplication>
#include <QPushButton>
#include <QBoxLayout>
#include <cmath>
#include <cstdlib>
#include <ctime>
class chouqian
{
	Q_OBJECT
	public:
	chouqian(QWidget*parent);
};
int main(int argc,char**argv)
//chouqian:chouqian(QWidget*parent=0)
//:QWidget(parent)
{
	srand(time(0));
	QApplication app(argc,argv);
	QLCDNumber lcd(3,0);
	int x=rand()%999;
	lcd.display(x);
	lcd.show();
	return app.exec();
}
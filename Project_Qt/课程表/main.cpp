#include <QApplication>
#include"table.h"

int main(int argc, char**argv)
{
	QApplication app(argc, argv);

	ClassTable ct;
	ct.show();

	app.exec();
}
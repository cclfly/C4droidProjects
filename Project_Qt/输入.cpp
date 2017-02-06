#include <QApplication>
#include "输入.h"

int main(int argc,char*argv[])
{
	QApplication app(argc,argv);
	AddressBook *addressBook=new AddressBook(0);
	addressBook->show( );
	return app.exec( );
}
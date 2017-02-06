/*
 * main.cpp
 */
#include <QApplication>
#include "cr.h"

int main(int argc,char *argv[])
{
	QApplication app(argc,argv);
	CR cr;
	cr.show();
	return app.exec();
}
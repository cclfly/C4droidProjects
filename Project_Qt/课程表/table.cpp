#include <QApplication>
#include <QFont>
#include "table.h"
#include <cstdio>
#include <QScreen>

char const*WeekNum(int n)
{
	switch (n)
	{
	case 1:
		return "星期一";
	case 2:
		return "星期二";
	case 3:
		return "星期三";
	case 4:
		return "星期四";
	case 5:
		return "星期五";
	case 6:
		return "星期六";
	case 7:
		return "星期天";
	default:
		return "ERROR";
	}
}

ClassTable::ClassTable(QWidget *prent = 0) :QWidget(prent)
{
	QScreen *iScreen = qApp->primaryScreen(); 
	QSize rScreenSize = iScreen->size();
	
	grid = new QGridLayout(this);

	this->setMinimumSize(rScreenSize.width(), rScreenSize.height());
	this->setMaximumSize(rScreenSize.width(), rScreenSize.height());

	char *str=new char[25];
	for (int i = 0; i < 5; i++)
	{
		sprintf(str, "<center>%s</center>", WeekNum(i + 1));
		week[i] = new QLabel(this);
		week[i]->setText(str);
		week[i]->setFont(QFont("楷书", 18));
		week[i]->setWordWrap(true);//�Զ�����
		week[i]->setStyleSheet("QLabel{border:1px solid purple}");
		week[i]->setGeometry(0, rScreenSize.width() / 12 + i * (rScreenSize.height() - rScreenSize.width() / 12) / 5, rScreenSize.width() / 12, (rScreenSize.height() - rScreenSize.width() / 12) / 5);
	}

	int sum = 0;
	for (int i = 0; i < 10; i++)
	{
		lesson[i] = new QLabel(this);
		sprintf(str, "<center>%d</center>", i + 1);
		lesson[i]->setText(str);
		switch (i)
		{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
			lesson[i]->setStyleSheet("QLabel{border:1px solid blue}");
			break;
		case 5:
		case 6:
		case 7:
			lesson[i]->setStyleSheet("QLabel{border:1px solid orange}");
			break;
		case 8:
		case 9:
			lesson[i]->setStyleSheet("QLabel{border:1px solid green}");
			break;
		}
		lesson[i]->setGeometry(sum += (rScreenSize.width() / 12 + ((i == 5 || i == 8) ? rScreenSize.width() / 24 : 0)), 0, rScreenSize.width() / 12, rScreenSize.width() / 12);
	}

	quit = new QPushButton("退出", this);
	quit->setFont(QFont("隶书", 11));
	quit->setGeometry(0, 0, rScreenSize.width() / 12, rScreenSize.width() / 12);
	quit->setStyleSheet("QPushButton{\
						border:1px solid black;\
						border-radius:2px;\
						padding:0px 0px 0px 0px;\
						}");
	QObject::connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));
}
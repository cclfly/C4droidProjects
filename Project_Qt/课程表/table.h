#pragma once

#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>

class ClassTable :public QWidget
{
	Q_OBJECT
public:
	ClassTable():ClassTable(0){};
	ClassTable(QWidget *prent);
private:
	QGridLayout *grid;
	QLabel *week[5];//����
	QLabel *lesson[10];//��ʱ
	QPushButton *quit;//�˳�
};
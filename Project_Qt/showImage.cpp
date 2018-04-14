#include <QApplication>
#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QLabel lab;
	QImage img("/storage/emulated/0/Tencent/qq_images/-5d13c49d9862ffe0.jpg");
	
	QDesktopWidget *deskWgt = QApplication::desktop();
	// 有效区域
	QRect availableRect = deskWgt->availableGeometry();
	// 屏幕分辨率
	QRect screenRect = deskWgt->screenGeometry();
	// 多屏总分辨率
	QRect virtualRect = deskWgt->geometry();
	
	img = img.scaled(availableRect.width(), availableRect.height());
	img = img.scaled(screenRect.width(), screenRect.height());
	img = img.scaled(virtualRect.width(), virtualRect.height());
	lab.setPixmap(QPixmap::fromImage(img));
	lab.show();
	app.exec();
}
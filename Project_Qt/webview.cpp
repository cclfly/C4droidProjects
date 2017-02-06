#include <QApplication>
#include <QUrl>
#include <QtWebKitWidgets/QWebView>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWebView v(0);
    v.load(QUrl("www.baidu.com"));
    v.show();
    return a.exec();
}
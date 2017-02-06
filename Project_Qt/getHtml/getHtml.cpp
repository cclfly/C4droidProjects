#include <QApplication>
#include <QEventLoop>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QWidget>
#include <QRegExp>
#include <QStringList>
#include <QLabel>

QString getHtml(QUrl url)
{
    QNetworkAccessManager manage;
    QNetworkReply *reply=manage.get(QNetworkRequest(url));
    QByteArray responseData;
    QEventLoop eventLoop;
    QWidget::connect(&manage,&QNetworkAccessManager::finished,&eventLoop,&QEventLoop::quit);
    eventLoop.exec();
    responseData=reply->readAll();
    return QString(responseData);
}

QStringList getHtmlUrl(QString dom)
{
    QRegExp rx;
    rx.setMinimal(true);
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    rx.setPattern("<a.*href=.*\"((http(s?)\\:)?//.*)\"");
    QStringList list;
    int pos=0;
    while((pos=rx.indexIn(dom,pos))!=-1)
    {
        QString tmp=rx.cap(1).split(QChar(' ')).at(0);
        list<<tmp;
        //qDebug()<<sl.at(0);
        pos+=rx.matchedLength();
    }
    return list;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QUrl url("http://www.baidu.com");
    QStringList sl=getHtmlUrl(getHtml(url));
    QString s;
    QLabel label;
    for(QString str:sl)
    {
        //qDebug()<<str;
        s+="<a href="+str+">"+str+"</a><br />\n";
        //label.setText(str);
    }
    label.setText(s);
    label.show();
    return a.exec();
}
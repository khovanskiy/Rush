#include "api.h"

API::API()
{
    networkManager = new QNetworkAccessManager(this);
    QObject::connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onResult(QNetworkReply*)));
}

API::~API()
{
    networkManager->deleteLater();
}

void API::onResult(QNetworkReply *reply)
{
    QString buffer = QString::fromUtf8(reply->readAll());
    //Console::print(buffer);
    QJsonDocument doc = QJsonDocument::fromJson(buffer.toUtf8());
    QJsonObject obj = doc.object();

    int result = obj.value("result").toVariant().toInt();
    if (result > 0)
    {
        QJsonArray arr = obj["data"].toArray();
        for (auto i = arr.begin(); i != arr.end(); ++i)
        {
            QJsonObject obj = (*i).toObject();
            Console::print(obj["name"].toString()+" "+obj["surname"].toString());
        }
    }
    else
    {
        Console::print("Api fail");
    }
    reply->deleteLater();
}

void API::request(const QString& act, const QVariantMap& params)
{
    QUrl url(QString("http://monplay.tw1.ru/api.php?act=") + act);
    QByteArray buffer;
    for (auto i = params.begin(); i != params.end(); ++i)
    {
        QString temp = i.key() + '=' + i.value().toString() + '&';
        buffer += temp;
    }
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    networkManager->post(request, buffer);
}

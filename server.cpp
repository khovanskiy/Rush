#include "server.h"

Server::Server()
{
    networkManager = new QNetworkAccessManager(this);
    QObject::connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onResult(QNetworkReply*)));
    QUrl url("http://monplay.tw1.ru/api.php");
    QNetworkRequest request(url);
    QNetworkReply *currentReply = networkManager->get(request);
    Console::print(currentReply);
}

Server::~Server()
{
    Console::print("Server has been deleted");
    delete networkManager;
}

void Server::onResult(QNetworkReply *reply)
{
    Console::print(reply);
    QString buffer = reply->readAll();
    Console::print(buffer);
    reply->close();
}

#include "networkclient.h"

NetworkClient::NetworkClient(QTcpSocket* socket)
{
    this->socket = socket;
    connect(socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(onReceive()));
}

NetworkClient::~NetworkClient()
{
    this->socket->deleteLater();
}

void NetworkClient::send(const QString &m)
{
    this->socket->write(m.toUtf8());
    this->socket->write("\n");
}

void NetworkClient::onDisconnected()
{
    invalidate();
}

void NetworkClient::onReceive()
{
    while (socket->canReadLine())
    {
        QString buffer = QString::fromUtf8(socket->readLine());
        Console::print(buffer);
    }
}

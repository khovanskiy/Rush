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
    Console::print("NetworkClient is deleted");
}

void NetworkClient::send(const QByteArray &m)
{
    this->socket->write(m);
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
        Console::print(QString("Client: ")+buffer);
        if (buffer == "auth\n")
        {
            Console::print("dispatch");
            dispatchEvent(GameObjectEvent(this, "tryauth"));
        }
        else
        {

        }
    }
}

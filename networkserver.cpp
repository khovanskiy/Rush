#include "networkserver.h"

NetworkServer::NetworkServer(const QString& host, const int port)
{
    this->host = host;
    this->port = port;
    server = new QTcpSocket(this);
    connect(server, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(server, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    connect(server, SIGNAL(readyRead()), this, SLOT(onRead()));
    connect(server, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));
    server->connectToHost(host, port);
}

NetworkServer::~NetworkServer()
{
    server->close();
    delete server;
}

void NetworkServer::onRead()
{
    while (server->canReadLine())
    {
        QString str = QString::fromUtf8(server->readLine());
        Console::print(QString("Server: ").append(str));
    }
}

void NetworkServer::onConnected()
{
    Console::print(QString("Connected to ").append(this->host+" ").append(QVariant(this->port).toString()));
}

void NetworkServer::onDisconnected()
{
    Console::print("Connection has been interrupted");
    invalidate();
}

void NetworkServer::onError(QAbstractSocket::SocketError)
{
    Console::print("Connection error");
}

void NetworkServer::send(const QString &message)
{
    server->write(message.toUtf8());
    server->write("\n");
}

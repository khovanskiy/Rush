#include "networkserver.h"

#include "gameobjectevent.h"
#include <QStringList>

NetworkServer::NetworkServer()
{

}

NetworkServer::~NetworkServer()
{
    server->close();
    delete server;
}


void NetworkServer::connect(const QString &host, const int port)
{
    this->host = host;
    this->port = port;
    server = new QTcpSocket(this);
    QObject::connect(server, SIGNAL(connected()), this, SLOT(onConnected()));
    QObject::connect(server, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    QObject::connect(server, SIGNAL(readyRead()), this, SLOT(onRead()));
    QObject::connect(server, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));
    server->connectToHost(host, port);
}

void NetworkServer::onRead()
{
    while (server->canReadLine())
    {
        QString str = QString::fromUtf8(server->readLine());
        parseResult(str);
    }
}

void NetworkServer::parseResult(const QString &result)
{
    //Console::print(result);
    Protocol* protocol = new Protocol();
    QStringList list = result.split(";");
    for (int i = 0; i < list.size(); ++i)
    {
        protocol->putString(list[i]);
    }
    dispatchEvent(NetworkEvent(this, NetworkEvent::PROTOCOL, protocol));
    delete protocol;
}

void NetworkServer::onConnected()
{
    Console::print(QString("Connected to ").append(this->host+" ").append(QVariant(this->port).toString()));
    dispatchEvent(NetworkEvent(this, NetworkEvent::CONNECTED));
}

void NetworkServer::onDisconnected()
{
    Console::print("Connection has been interrupted");
    dispatchEvent(NetworkEvent(this, NetworkEvent::DISCONNECTED));
}

void NetworkServer::onError(QAbstractSocket::SocketError)
{
    Console::print("Connection error");
}

void NetworkServer::send(Protocol &protocol)
{
    server->write(protocol.toByteArray());
}

#include "networkserver.h"

#include "gameobjectevent.h"
#include <QStringList>
#include <QNetworkInterface>
#include "multicastparams.h"

NetworkServer::NetworkServer()
{

}

NetworkServer::~NetworkServer()
{
    tcp_socket->close();
    delete tcp_socket;
}


void NetworkServer::connect(const QString &host, const int port)
{
    this->host = host;
    this->port = port;
    multicast_socket = new QUdpSocket();
    multicast_socket->bind(QHostAddress::AnyIPv4, MulticastParams::getGroupPort(),
                    QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
    QHostAddress groupAddress = MulticastParams::getGroupAddress();
    for (auto it = interfaces.begin(); it != interfaces.end(); it++) {
        if (it->CanMulticast && it->IsRunning && it->isValid()) {
            multicast_socket->joinMulticastGroup(groupAddress, *it);
        }
    }
    QObject::connect(multicast_socket, SIGNAL(readyRead()), this, SLOT(onMulticastRead()));
    tcp_socket = new QTcpSocket(this);
    QObject::connect(tcp_socket, SIGNAL(connected()), this, SLOT(onTcpConnected()));
    QObject::connect(tcp_socket, SIGNAL(disconnected()), this, SLOT(onTcpDisconnected()));
    QObject::connect(tcp_socket, SIGNAL(readyRead()), this, SLOT(onTcpRead()));
    QObject::connect(tcp_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onTcpError(QAbstractSocket::SocketError)));
    tcp_socket->connectToHost(host, port);
}

void NetworkServer::onMulticastRead()
{
    while (multicast_socket->hasPendingDatagrams()) {
        // Create a temporary buffer ...
        QByteArray datagram;

        // ... with the size of the received multicast datagram ...
        datagram.resize(multicast_socket->pendingDatagramSize());

        // ... and copy over the received multicast datagram into that buffer.
        multicast_socket->readDatagram(datagram.data(), datagram.size());
        QString str = QString::fromUtf8(datagram.data());
        Console::print(str);
        parseResult(str);
    }
}

void NetworkServer::onTcpRead()
{
    while (tcp_socket->canReadLine())
    {
        QString str = QString::fromUtf8(tcp_socket->readLine());
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

void NetworkServer::onTcpConnected()
{
    Console::print(QString("Connected to ").append(this->host+" ").append(QVariant(this->port).toString()));
    dispatchEvent(NetworkEvent(this, NetworkEvent::CONNECTED));
}

void NetworkServer::onTcpDisconnected()
{
    Console::print("Connection has been interrupted");
    dispatchEvent(NetworkEvent(this, NetworkEvent::DISCONNECTED));
}

void NetworkServer::onTcpError(QAbstractSocket::SocketError e)
{
    Console::print("Check");
    //Console::print(e);
    Console::print("Connection error ");
}

void NetworkServer::send(Protocol &protocol)
{
    tcp_socket->write(protocol.toByteArray());
}

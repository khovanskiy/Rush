#ifndef NETWORKSERVER_H
#define NETWORKSERVER_H

#include <QObject>
#include <QTcpSocket>
#include <QUdpSocket>

#include "common/gamemodelobject.h"
#include "common/console.h"
#include "common/protocol.h"
#include "networkevent.h"

class NetworkServer : public QObject, public EventDispatcher {
Q_OBJECT
public:
    NetworkServer();

    ~NetworkServer();

    void connect(const QString &host, const quint16 port);

    void send(Protocol &);

protected:
    void parseResult(const QString &);

private:
    QTcpSocket *tcp_socket;
    QUdpSocket *multicast_socket;
    QString host;
    int port;
private slots:

    void onTcpRead();

    void onMulticastRead();

    void onTcpError(QAbstractSocket::SocketError);

    void onTcpConnected();

    void onTcpDisconnected();
};

#endif // NETWORKSERVER_H

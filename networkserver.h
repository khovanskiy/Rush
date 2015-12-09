#ifndef NETWORKSERVER_H
#define NETWORKSERVER_H

#include <QObject>
#include <QTcpSocket>

#include "common/gamemodelobject.h"
#include "common/console.h"
#include "common/protocol.h"
#include "networkevent.h"

class NetworkServer : public QObject, public EventDispatcher
{
    Q_OBJECT
public:
    NetworkServer();
    ~NetworkServer();

    void connect(const QString& host, const int port);
    void send(Protocol&);
protected:
    void parseResult(const QString&);
private:
    QTcpSocket* server;
    QString host;
    int port;
private slots:
    void onRead();
    void onError(QAbstractSocket::SocketError);
    void onConnected();
    void onDisconnected();
};

#endif // NETWORKSERVER_H

#ifndef NETWORKSERVER_H
#define NETWORKSERVER_H

#include <QObject>
#include <QTcpSocket>

#include "gamemodelobject.h"
#include "console.h"

class NetworkServer : public QObject, public GameModelObject
{
    Q_OBJECT
public:
    NetworkServer(const QString& host, const int port);
    ~NetworkServer();
    void send(const QString&);
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

#ifndef NETWORKPLAYER_H
#define NETWORKPLAYER_H

#include <QObject>
#include <QTcpSocket>

#include "networkobject.h"
#include "networkevent.h"
#include "gameobjectevent.h"
#include "common/console.h"

class NetworkClient : public QObject, public NetworkObject
{
    Q_OBJECT
public:
    NetworkClient(QTcpSocket* socket);
    virtual ~NetworkClient();
    void send(const QByteArray&);
protected slots:
    void onDisconnected();
    void onReceive();
private:
    QTcpSocket* socket;
};

#endif // NETWORKPLAYER_H

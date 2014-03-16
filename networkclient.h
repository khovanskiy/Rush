#ifndef NETWORKPLAYER_H
#define NETWORKPLAYER_H

#include <QObject>
#include <QTcpSocket>

#include "gamemodelobject.h"
#include "console.h"

class NetworkClient : public QObject, public GameModelObject
{
    Q_OBJECT
public:
    NetworkClient(QTcpSocket* socket);
    virtual ~NetworkClient();
    void send(const QString&);
protected slots:
    void onDisconnected();
    void onReceive();
private:
    QTcpSocket* socket;
};

#endif // NETWORKPLAYER_H

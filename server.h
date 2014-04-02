#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QMainWindow>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include <QElapsedTimer>
#include <vector>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "networkclient.h"
#include "console.h"
#include "api.h"

class Server : public QMainWindow, public GameModelObject
{
    Q_OBJECT
public:
    Server();
    virtual ~Server();
    virtual void tick(double dt);
    void broadcast(const QString&);
public slots:
    void onLoop();
    //void onResult(QNetworkReply* reply);
protected slots:
    void onClientConnected();
    void onClientDisconnected();
protected:
    void init();
private:
    std::vector<NetworkClient*> players;

    int port;
    QTcpServer* p_server;

    QElapsedTimer* counter;
    QTimer* loop;
    int TICKS_PER_SECOND;
    int SKIP_TICKS;
    int MAX_FRAMESKIP;
    long next_game_tick;
};

#endif // SERVER_H

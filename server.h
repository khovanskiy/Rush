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
#include <QCoreApplication>

#include "networkclient.h"
#include "common/console.h"
#include "api.h"

#include "serverstate.h"

class Server : public QCoreApplication, public EventHandler
{
    Q_OBJECT
public:
    Server(int argc, char** argv);
    virtual ~Server();
public slots:
    void onLoop();
private:
    ServerState* state;
    QElapsedTimer* counter;
    QTimer* loop;
    int TICKS_PER_SECOND;
    int SKIP_TICKS;
    int MAX_FRAMESKIP;
    long next_game_tick;    
};

#endif // SERVER_H

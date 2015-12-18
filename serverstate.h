#ifndef SERVERSTATE_H
#define SERVERSTATE_H

#include "common/state.h"
#include "networkclient.h"
#include <QTcpServer>
#include <QUdpSocket>
#include <QHostAddress>
#include <QObject>
#include <QNetworkInterface>
#include <vector>
#include <stack>
#include "gameworld.h"
#include "common/physicsworld.h"
#include "idsystem.h"
#include "common/vehicle.h"
#include "common/obstacle.h"
#include "common/protocol.h"

#define PLAYER_WAIT_VEHICLE 1
#define PLAYER_HAS_VEHICLE 2

class Player : public QObject, public EventHandler
{
    Q_OBJECT
signals:
    void disconnected();
    void readyRead();
public:
    Player(int id_player, QTcpSocket* socket)
    {
        this->id_player = id_player;
        this->socket = socket;
        ticks = 0;
        count_kills = 0;
        count_dieds = 0;
        state = PLAYER_WAIT_VEHICLE;
        connect(socket, SIGNAL(disconnected()), this, SIGNAL(disconnected()));
        connect(socket, SIGNAL(readyRead()), this, SIGNAL(readyRead()));
        Console::print(QString("Player created #") + QVariant(id_player).toString());
    }
    ~Player()
    {
        socket->close();
        delete socket;
        Console::print(QString("Player deleted #") + QVariant(id_player).toString());
    }
    void Invoke(const Event &event)
    {
        if (event.type == Event::INVALIDATE)
        {
            state = PLAYER_WAIT_VEHICLE;
            ticks = 100;
            Console::print("Now waiting new vehicle");
            vehicle = 0;
        }
    }
    int count_kills;
    int count_dieds;

    int id_player;
    QTcpSocket* socket;
    Vehicle* vehicle;
    int ticks;
    int state;
};

class ServerState : public QObject, public State, public EventHandler
{
    Q_OBJECT
public:
    void init();
    void tick(double dt);
    void release();
    void Invoke(const Event &);
public slots:
    void playerConnected();
    void playerDisconnected();
    void playerRecieved();
protected:
    void tcpBroadcastPlayerStat(Player*);
    void tcpBroadcast(Protocol& buffer);
    void multicast(Protocol& buffer, bool forceSend = false);
    void multicastObjects();
    void multicastVehicle(Vehicle* vehicle, int id_parent);
    void multicastPhysicsObject(PhysicsObject* object, int id_parent);
    void tcpBroadcastInvalidate(GameModelObject* object);
    void parseResult(Protocol& protocol);
private:
    IDSystem players_ids;
    IDSystem objects_ids;
    std::map<int, Player*> players;

    QTcpServer* tcp_server;
    QUdpSocket* multicast_socket;
    QHostAddress group_address;
    int group_port;
    std::vector<QNetworkInterface> multicast_interfaces;

    GameWorld* game_world;
    PhysicsWorld* physics_world;
    int next_player_id;
    int next_object_id;
};

#endif // SERVERSTATE_H

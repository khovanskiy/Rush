#ifndef SERVERSTATE_H
#define SERVERSTATE_H

#include "state.h"
#include "networkclient.h"
#include <QTcpServer>
#include <QObject>
#include <vector>
#include <stack>
#include "gameworld.h"
#include "physicsworld.h"
#include "idsystem.h"
#include "vehicle.h"
#include "obstacle.h"
#include "protocol.h"

#define PLAYER_WAIT_VEHICLE 1
#define PLAYER_HAS_VEHICLE 2

class Player : public QObject, public EventHandler
{
    Q_OBJECT
signals:
    void disconected();
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
        connect(socket, SIGNAL(disconnected()), this, SIGNAL(disconected()));
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
    void broadcastPlayerStat(Player*);
    void broadcast(Protocol& buffer);
    void broadcastObjects();
    void broadcastVehicle(Vehicle* vehicle, int id_parent);
    void broadcastPhysicsObject(PhysicsObject* object, int id_parent);
    void broadcastInvalidate(GameModelObject* object);
    void parseResult(Protocol& protocol);
private:
    IDSystem players_ids;
    IDSystem objects_ids;
    std::map<int, Player*> players;

    QTcpServer* server;
    GameWorld* game_world;
    PhysicsWorld* physics_world;
    int next_player_id;
    int next_object_id;
};

#endif // SERVERSTATE_H

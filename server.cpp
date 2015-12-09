#include "server.h"
#include <iostream>

Server::Server()
{
    state = new ServerState();
    state->init();

    counter = new QElapsedTimer();
    loop = new QTimer();
    connect(loop, SIGNAL(timeout()), this, SLOT(onLoop()));

    TICKS_PER_SECOND = 20;
    std::cout << "TICKS PER SECOND = " << 21 << std::endl;
    SKIP_TICKS = 1000 / TICKS_PER_SECOND;
    MAX_FRAMESKIP = 10;
    counter->start();
    next_game_tick = counter->elapsed();
    loop->start(0);

    //QVariantMap map;
    //map.insert("login", "kabanov");
    //map.insert("password", "");
    //map.insert("uids", "1,2");
    //API::gi().request("users.getInfo", map);

}

Server::~Server()
{
    state->release();
}

/*void Server::init()
{
    port = 560;
    p_server = new QTcpServer(this);
    if (!p_server->listen(QHostAddress::Any, port))
    {
        Console::print("Connection failed");
        p_server->close();
    }
    else
    {
        Console::print(QString("Server has started at port: ") + QVariant(port).toString());
    }
    connect(p_server, SIGNAL(newConnection()), this, SLOT(onClientConnected()));

    game_world = new GameWorld();
    physics_world = new PhysicsWorld();

    next_player_id = 1;
    next_object_id = 1;

    /*car = new Vehicle(1, new Rectangle2D(Point2D(0,0), 1.962, 4.710), 1887);
    double r[] = {3.59, 2.19, 1.41, 1, 0.83};
    std::vector<double> ratios(r, r + sizeof(r) / sizeof(double));
    car->setEngine(VehicleEngine(637, 6000, ratios, 3.06));
    CarTrack back(-1.62724, 1.604, 1000 / (2 * M_PI * 456), 0.466, true, true, RotationReaction::NoRotation, 0.9, 0.025, 1.5, 1.5, M_PI / 6);
    CarTrack front(1.74552, 1.603, 1000 / (2 * M_PI * 456), 0.544, false, true, RotationReaction::StraightRot, 0.9, 0.025, 1.5, 1.5, M_PI / 6);
    car->setWheels(back, front, 1.45);
    car->setVehicleBody(VehicleBody(0.356, 5.0, 1.923, 1.45, car->chassis.getMassCenter()));
    car->setCoordinates(Vector2D(-10, 0));
    car->setAngle(-asin(1));
    car->setTorquePercent(0.1);
    car->setAccelerationState(AccelerationState::ForwardAcc);

    Turret* t = new Turret(2, new Rectangle2D(Point2D(0, -0.5), 1.5, 1.5), 100, 7, 0.1, 2 * asin(1), Bullet::BULLET, 0);
    car->addTurret(t);

   // game_world->add(car);
   // physics_world->add(car);
}*/

/*QByteArray Server::prepareEvent(const GameObjectEvent& event)
{
    QByteArray buffer;
    buffer.append(event.type + ";");
    buffer.append(QVariant(event.id_player).toString()  + ";");
    buffer.append(QVariant(event.id_object).toString() + ";");
    buffer.append(QVariant(event.id_parent).toString() + ";");
    buffer.append(QVariant(event.class_object).toString() + ";");
    buffer.append(QVariant(event.type_object).toString() + ";");
    buffer.append(QVariant(event.position.x).toString() + ";");
    buffer.append(QVariant(event.position.y).toString() + ";");
    buffer.append(QVariant(event.rotation).toString());
    return buffer;
}*/

/*void Server::Invoke(const Event &event)
{
    Console::print(QString("Invoke: ")+event.type);
    if (event.type == "tryauth")
    {
        Console::print("tryauth");
        GameObjectEvent e(0, GameObjectEvent::AUTHORIZED);
        e.id_player = next_player_id;
        next_player_id++;
        broadcast(prepareEvent(e));

        GameObjectEvent e2(0, GameObjectEvent::ADDED_OBJECT);
        e2.id_player = e.id_player;
        e2.id_object = next_object_id;
        e2.class_object = GameObjectType::VEHICLE;
        e2.type_object = 1;
        e2.position.x = 0;
        e2.position.y = 0;
        e2.rotation = 1;
        next_object_id++;
        broadcast(prepareEvent(e2));
    }
}*/

/*void Server::onClientConnected()
{
    Console::print("Client connected");
    QTcpSocket* socket = p_server->nextPendingConnection();
    NetworkClient* player = new NetworkClient(socket);
    Console::print("add listener");
    player->addEventListener(this);
    players.push_back(player);
}

void Server::onClientDisconnected()
{
    Console::print("Client disconnected");
}

void Server::broadcast(const QByteArray& buffer)
{
    //Console::print(QString("Broadcast: "+message));
    for (int i = 0; i < players.size(); ++i)
    {
        if (players[i]->isValid())
        {
            players[i]->send(buffer);
        }
        else
        {
            delete players[i];
            players[i] = players[players.size() - 1];
            players.pop_back();
            --i;
        }
    }
}*/

void Server::onLoop()
{
    int loops = 0;
    while (counter->elapsed() > next_game_tick && loops < MAX_FRAMESKIP)
    {
        state->tick(1.0 / TICKS_PER_SECOND);
        next_game_tick += SKIP_TICKS;
        loops++;
    }
}

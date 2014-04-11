#include "serverstate.h"
#include "physicsobjectfactory.h"
#include "terrain.h"
#include "random.h"

static const double M_PI = 3.14159265358979323846;

void ServerState::init()
{
    game_world = new GameWorld();
    physics_world = new PhysicsWorld();
    server = new QTcpServer();
    connect(server, SIGNAL(newConnection()), this, SLOT(playerConnected()));
    if (server->listen(QHostAddress::Any, 560))
    {
        Console::print("Server is running...");
    }

    /*for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            Terrain* t = new Terrain(objects_ids.next());
            t->setPosition(Vector2D(i * 30, j * 30));
            game_world->add(t);
        }
    }*/

    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
            Terrain* terrain = new Terrain(objects_ids.next());
            terrain->setPosition(Vector2D(100 * i, 100 * j));
            game_world->add(terrain);
        }
    }

    for (int i = 0; i < 10; ++i)
    {
        Obstacle* wall = PhysicsObjectFactory::createObstacle(objects_ids.next(), 0);
        wall->setCoordinates(Vector2D(10 + 20 * i, -1));
        game_world->add(wall);
        physics_world->add(wall);
    }

    for (int i = 0; i < 10; ++i)
    {
        Obstacle* wall = PhysicsObjectFactory::createObstacle(objects_ids.next(), 0);
        wall->setCoordinates(Vector2D(10 + 20 * i, 201));
        game_world->add(wall);
        physics_world->add(wall);
    }

    for (int i = 0; i < 10; ++i)
    {
        Obstacle* wall = PhysicsObjectFactory::createObstacle(objects_ids.next(), 0);
        wall->setCoordinates(Vector2D(-1, 10 + 20 * i));
        wall->setAngle(M_PI/2);
        game_world->add(wall);
        physics_world->add(wall);
    }

    for (int i = 0; i < 10; ++i)
    {
        Obstacle* wall = PhysicsObjectFactory::createObstacle(objects_ids.next(), 0);
        wall->setCoordinates(Vector2D(201, 10 + 20 * i));
        wall->setAngle(M_PI/2);
        game_world->add(wall);
        physics_world->add(wall);
    }
}

void ServerState::Invoke(const Event &event)
{
    if (event.type == "DESTROY_BY")
    {
        const GameObjectEvent* e = static_cast<const GameObjectEvent*>(&event);
        int id_from = 0;
        int id_to = 0;
        for (std::map<int, Player*>::iterator i = players.begin(); i != players.end(); ++i)
        {
            Player* current = (*i).second;
            if (current->vehicle == e->target)
            {
                id_from = (*i).first;
            }
            else if (current->vehicle == e->subject)
            {
                id_to = (*i).first;
            }
        }
        if (id_from != 0 && id_to != 0)
        {
            Console::print(QString("Player #")+QVariant(id_from).toString()+" have been killed by Player #"+QVariant(id_to).toString());
            Player* from = players[id_from];
            from->count_dieds++;
            Player* to = players[id_to];
            to->count_kills++;
            //broadcastPlayerStat(from);
            //broadcastPlayerStat(to);
        }
    }
    else if (event.type == Event::INVALIDATE)
    {
        GameModelObject* object = static_cast<GameModelObject*>(event.target);
        Console::print(QString("Object #")+QVariant(object->my_id).toString()+" is destroyed");
        broadcastInvalidate(object);
    }
    else if (event.type == "TURRET_FIRE")
    {
        const GameObjectEvent* e = static_cast<const GameObjectEvent*>(&event);
        Vehicle* obj = static_cast<Vehicle*>(event.target);
        Matrix A = obj->getTransform();
        Matrix B = obj->getTurrets()[0]->getTransform();

        Matrix m = Matrix::mul(obj->getTransform(), obj->getTurrets()[0]->getTransform()).invert();
        Vector2D p(0, 1);
        p.rotate(obj->getAngle()+obj->getTurrets()[0]->getAngle());
        p.normalize();
        p.mul(25);

        Bullet* b = new Bullet(objects_ids.next(), m.map(e->position), p, 1, Bullet::BULLET, 0.15, 0.43, 0.05, 3);
        Vector2D new_speed = b->getSpeed();
        new_speed.setLength(new_speed.getLength() + obj->getSpeed().getLength());
        b->setSpeed(new_speed);
        b->setSource(obj);
        b->addEventListener(this);
        game_world->add(b);
        physics_world->add(b);
    }
}

void ServerState::tick(double dt)
{
    physics_world->tick(dt);
    game_world->tick(dt);
    broadcastObjects();

    for (std::map<int, Player*>::iterator i = players.begin(); i != players.end(); ++i)
    {
        Player* player = (*i).second;
        if (player->state == PLAYER_WAIT_VEHICLE)
        {
            if (player->ticks > 0)
            {
                player->ticks--;
            }
            else
            {
                Vehicle* vehicle = PhysicsObjectFactory::createVehicle(objects_ids.next(), rand() % 3);
                Turret* turret = PhysicsObjectFactory::createTurret(objects_ids.next(), 1);
                player->vehicle = vehicle;
                player->state = PLAYER_HAS_VEHICLE;

                Vector2D pos;
                switch (player->id_player % 4)
                {
                case 0:
                {
                    pos.x = Random::getRandom(5, 95);
                    pos.y = Random::getRandom(5, 95);
                } break;
                case 1:
                {
                    pos.x = Random::getRandom(105, 195);
                    pos.y = Random::getRandom(5, 95);
                } break;
                case 2:
                {
                    pos.x = Random::getRandom(5, 95);
                    pos.y = Random::getRandom(105, 195);
                } break;
                case 3:
                {
                    pos.x = Random::getRandom(105, 195);
                    pos.y = Random::getRandom(105, 195);
                } break;
                }


                vehicle->setCoordinates(pos);
                vehicle->addEventListener(player);
                vehicle->addEventListener(this);
                vehicle->addTurret(turret);

                game_world->add(vehicle);
                physics_world->add(vehicle);

                Protocol protocol;
                protocol.putInt(ADD_OBJECT);
                protocol.putInt(player->id_player);
                protocol.putInt(vehicle->my_id);
                broadcast(protocol);

            }
        }
        broadcastPlayerStat(player);
    }
}

void ServerState::broadcastPlayerStat(Player* player)
{
    Protocol protocol;
    protocol.putInt(PLAYER_STAT);
    protocol.putInt(player->id_player);
    protocol.putInt(player->count_kills);
    protocol.putInt(player->count_dieds);
    if (player->vehicle)
    {
        protocol.putInt(player->vehicle->health);
        protocol.putDouble(player->vehicle->getSpeed().getLength());
        //protocol.putDouble(player->vehicle->ge);
    }
    else
    {
        protocol.putInt(0);
        protocol.putDouble(0.0);
    }
    broadcast(protocol);
}

void ServerState::broadcastObjects()
{
    std::vector<GameModelObject*> inners = game_world->getInners();
    for (int i = 0; i < inners.size(); ++i)
    {
        if (inners[i]->getFamilyId() == GameObjectType::VEHICLE)
        {
            Vehicle* object = static_cast<Vehicle*>(inners[i]);
            broadcastVehicle(object, 0);
        }
        else if (inners[i]->getFamilyId() == GameObjectType::BULLET)
        {
            PhysicsObject* object = static_cast<PhysicsObject*>(inners[i]);
            broadcastPhysicsObject(object, 0);
        }
        else if (inners[i]->getFamilyId() == GameObjectType::OBSTACLE)
        {
            PhysicsObject* object = static_cast<PhysicsObject*>(inners[i]);
            broadcastPhysicsObject(object, 0);
        }
        else if (inners[i]->getFamilyId() == GameObjectType::TERRAIN)
        {
            Terrain* object = static_cast<Terrain*>(inners[i]);
            Protocol protocol;
            protocol.putInt(UPDATE_OBJECT);
            protocol.putInt(object->my_id);
            protocol.putInt(0);
            protocol.putInt((int)object->getFamilyId());
            protocol.putInt(object->type_object);
            protocol.putDouble(object->getPosition().x);
            protocol.putDouble(object->getPosition().y);
            protocol.putDouble(0);
            broadcast(protocol);
        }
    }
}

void ServerState::broadcastVehicle(Vehicle* vehicle, int id_parent)
{
    broadcastPhysicsObject(vehicle, id_parent);
    std::vector<Turret*> turrets = vehicle->getTurrets();
    for (int i = 0; i < turrets.size(); ++i)
    {
        broadcastPhysicsObject(turrets[i], vehicle->my_id);
    }
}

void ServerState::broadcastPhysicsObject(PhysicsObject* object, int id_parent)
{
    Protocol protocol;
    protocol.putInt(UPDATE_OBJECT);
    protocol.putInt(object->my_id);
    protocol.putInt(id_parent);
    protocol.putInt((int)object->getFamilyId());
    protocol.putInt(object->type_object);
    protocol.putDouble(object->getCoordinates().x);
    protocol.putDouble(object->getCoordinates().y);
    protocol.putDouble(object->getAngle());
    broadcast(protocol);
}

void ServerState::broadcast(Protocol &protocol)
{
    QByteArray buffer = protocol.toByteArray();
    for (std::map<int, Player*>::iterator i = players.begin(); i != players.end(); ++i)
    {
        Player* current = (*i).second;
        current->socket->write(buffer);
    }
}

void ServerState::release()
{
    delete physics_world;
    delete game_world;
}

void ServerState::playerConnected()
{
    Player* player = new Player(players_ids.next(), server->nextPendingConnection());
    players[player->id_player] = player;
    connect(player, SIGNAL(disconected()), this, SLOT(playerDisconnected()));
    connect(player, SIGNAL(readyRead()), this, SLOT(playerRecieved()));

    /*Vehicle* vehicle = PhysicsObjectFactory::createVehicle(objects_ids.next(), 2);
    Turret* turret = PhysicsObjectFactory::createTurret(objects_ids.next(), 1);
    player->vehicle = vehicle;
    vehicle->addEventListener(player);
    vehicle->addEventListener(this);
    vehicle->addTurret(turret);

    game_world->add(vehicle);
    physics_world->add(vehicle);*/

    Protocol protocol;
    protocol.putInt(AUTH);
    protocol.putInt(player->id_player);
    player->socket->write(protocol.toByteArray());

    protocol.clear();

    for (std::map<int, Player*>::iterator i = players.begin(); i != players.end(); ++i)
    {
        Player* current = (*i).second;
        if (current->id_player != player->id_player)
        {
            protocol.putInt(LOGIN);
            protocol.putInt(current->id_player);
            player->socket->write(protocol.toByteArray());
        }
    }
    protocol.clear();

    protocol.putInt(LOGIN);
    protocol.putInt(player->id_player);
    broadcast(protocol);

    /*protocol.clear();
    protocol.putInt(ADD_OBJECT);
    protocol.putInt(player->id_player);
    protocol.putInt(vehicle->my_id);
    broadcast(protocol);*/
}

void ServerState::playerRecieved()
{
    Player* player = static_cast<Player*>(sender());
    while (player->socket->canReadLine())
    {
        QString str = QString::fromUtf8(player->socket->readLine());
        Protocol protocol;
        QStringList list = str.split(";");
        for (int i = 0; i < list.size(); ++i)
        {
            protocol.putString(list[i]);
        }
        parseResult(protocol);
    }
}

void ServerState::playerDisconnected()
{
    Player* player = static_cast<Player*>(sender());
    disconnect(player, SIGNAL(disconected()), this, SLOT(playerDisconnected()));
    Vehicle* vehicle = player->vehicle;
    int id_player = player->id_player;
    players.erase(player->id_player);
    players_ids.release(player->id_player);
    player->deleteLater();

    if (vehicle)
    {
        broadcastInvalidate(vehicle);
        vehicle->invalidate();
    }

    Protocol protocol;
    protocol.putInt(LOGOUT);
    protocol.putInt(id_player);
    broadcast(protocol);
}

void ServerState::broadcastInvalidate(GameModelObject *object)
{
    Protocol protocol;
    protocol.putInt(REMOVE_OBJECT);
    protocol.putInt(object->my_id);
    broadcast(protocol);
}

void ServerState::parseResult(Protocol& protocol)
{
    int action = protocol.nextInt();
    if (action == PLAYER_IO)
    {
        int id_player = protocol.nextInt();
        AccelerationState acc_state = (AccelerationState)protocol.nextInt();
        double rotation_percent = protocol.nextDouble();
        bool firing_state = (bool)protocol.nextInt();
        Vector2D target;
        target.x = protocol.nextDouble();
        target.y = protocol.nextDouble();


        Player* player = players[id_player];
        if (player->vehicle)
        {
            player->vehicle->setTorquePercent(1);
            player->vehicle->setAccelerationState(acc_state);
            player->vehicle->setRotationPercent(rotation_percent);
            player->vehicle->setFiring(firing_state);
            player->vehicle->turretsToPoint(target);
        }
    }
}

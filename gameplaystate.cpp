#include "gameplaystate.h"

static const double M_PI = 3.14159265358979323846;

#include "thread.h"
#include "random.h"
#include "gameobjectevent.h"
#include "physicsobjectfactory.h"

void GameplayState::init()
{
    game_world = new GameWorld();
    server = new NetworkServer();
    server->addEventListener(this);
    server->connect("127.0.0.1", 560);

    map_view = new MapView(game_world);

    current_state = WAIT_VEHICLE;
    controls = 0;
    camera_controls = 0;
    current_vehicle = 0;
    current_id_player = 0;
    current_id_vehicle = 0;

    Mouse::gi()->addEventListener(this);
    Keyboard::gi()->addEventListener(this);
}

void GameplayState::Invoke(const Event &event)
{
    if (event.type == KeyboardEvent::KEY_UP)
    {
        const KeyboardEvent* e = static_cast<const KeyboardEvent*>(&event);
        if (e->keyCode == Qt::Key_Escape)
        {
            context->changeState(StateEnum::GAMEPLAY);
        }
    }
    else if (event.type == NetworkEvent::PROTOCOL)
    {
        const NetworkEvent* e = static_cast<const NetworkEvent*>(&event);
        Protocol* protocol = e->protocol;
        int action = protocol->nextInt();
        if (action == UPDATE_OBJECT)
        {
            int id_object = protocol->nextInt();
            int id_parent = protocol->nextInt();
            GameObjectType class_object = (GameObjectType)protocol->nextInt();
            int type_object = protocol->nextInt();
            Vector2D position;
            position.x = protocol->nextDouble();
            position.y = protocol->nextDouble();
            double rotation = protocol->nextDouble();
            GameModelObject* object = GameModelObject::findById(id_object);
            GameModelObject* parent = GameModelObject::findById(id_parent);
            if (object != 0)
            {
                if (object->getFamilyId() != GameObjectType::TERRAIN)
                {
                    PhysicsObject* physics_object = static_cast<PhysicsObject*>(object);
                    physics_object->setCoordinates(position);
                    physics_object->setAngle(rotation);
                }
            }
            else
            {
                switch (class_object)
                {
                case GameObjectType::TERRAIN:
                {
                    Terrain* terrain = new Terrain(id_object);
                    terrain->setPosition(position);
                    game_world->add(terrain);
                } break;
                case GameObjectType::VEHICLE:
                {
                    Vehicle* vehicle = PhysicsObjectFactory::createVehicle(id_object, type_object);
                    vehicle->setCoordinates(position);
                    vehicle->setAngle(rotation);
                    game_world->add(vehicle);
                } break;
                case GameObjectType::OBSTACLE:
                {
                    Obstacle* obstacle = PhysicsObjectFactory::createObstacle(id_object, type_object);
                    obstacle->setCoordinates(position);
                    obstacle->setAngle(rotation);
                    game_world->add(obstacle);
                } break;
                case GameObjectType::BULLET:
                {
                    Bullet* bullet = PhysicsObjectFactory::createBullet(id_object,position,rotation, type_object, 0.05);
                    game_world->add(bullet);
                } break;
                case GameObjectType::TURRET:
                {
                    Vehicle* vehicle = static_cast<Vehicle*>(parent);
                    Turret* turret = PhysicsObjectFactory::createTurret(id_object, type_object);
                    turret->setCoordinates(position);
                    turret->setAngle(rotation);
                    vehicle->addTurret(turret);
                }
                }
            }
        }
        else if (action == AUTH)
        {
            current_id_player = protocol->nextInt();
            Console::print(QString("My id player #") + QVariant(current_id_player).toString());
        }
        else if (action == LOGIN)
        {
            int id_player = protocol->nextInt();
            if (id_player != current_id_player)
            {
                Console::print(QString("Player #") + QVariant(id_player).toString() + " logged IN");
            }
        }
        else if (action == LOGOUT)
        {
            int id_player = protocol->nextInt();
            if (id_player != current_id_player)
            {
                Console::print(QString("Player #") + QVariant(id_player).toString() + " logged OUT");
            }
        }
        else if (action == ADD_OBJECT)
        {
            int id_player = protocol->nextInt();
            int id_object = protocol->nextInt();
            Console::print("id player");
            Console::print(id_player);
            if (id_player == current_id_player)
            {
                Console::print(QString("ID OBJECT: ") + QVariant(id_object).toString());
                current_id_vehicle = id_object;
                current_state = NEED_INIT_VEHICLE;
            }
        }
        else if (action == REMOVE_OBJECT)
        {
            int id_object = protocol->nextInt();
            GameModelObject* obj = GameModelObject::findById(id_object);
            if (obj != 0)
            {
                if (current_id_vehicle == obj->my_id)
                {
                    Console::print("I am dead");
                    current_state = WAIT_VEHICLE;
                    current_id_vehicle = 0;
                    delete camera_controls;
                    camera_controls = 0;
                    delete controls;
                    controls = 0;
                    current_vehicle = 0;
                }
                obj->invalidate();
            }
        }
    }
}

void GameplayState::render(const RenderData &render_data)
{
    map_view->render(render_data);
    if (camera_controls != 0)
    {
        camera_controls->update();
    }
}

void GameplayState::tick(double dt)
{
    game_world->tick(dt);

    if (current_id_vehicle != 0)
    {
        if (current_state == NEED_INIT_VEHICLE)
        {
            GameModelObject* model = GameModelObject::findById(current_id_vehicle);
            if (model != 0)
            {
                current_vehicle = static_cast<Vehicle*>(model);
                controls = new UIVehicleController(current_vehicle);
                camera_controls = new CameraController(current_vehicle);
                current_state = INITED;
            }
        }
        if (current_state == INITED)
        {
            Protocol protocol;
            protocol.putInt(PLAYER_IO);
            protocol.putInt(current_id_player);
            protocol.putInt(current_vehicle->acc_state);
            protocol.putDouble(current_vehicle->rotation_percent);

            protocol.putInt(current_vehicle->firing_state);
            Vector2D target = Camera::gi()->getTransform().invert().map(Mouse::gi()->position());
            protocol.putDouble(target.x);
            protocol.putDouble(target.y);

            server->send(protocol);
        }
    }
}

void GameplayState::release()
{
    Keyboard::gi()->removeEventListener(this);
    Mouse::gi()->removeEventListener(this);

    server->deleteLater();

    delete camera_controls;

    delete controls;
    delete server;
    delete map_view;
    delete game_world;
}

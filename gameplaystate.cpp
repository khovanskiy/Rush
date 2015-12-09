#include "gameplaystate.h"

#include "thread.h"
#include "random.h"
#include "gameobjectevent.h"

std::map<int, WorkView*> WorkView::cache_work;

void GameplayState::init()
{
    server = new NetworkServer();
    server->addEventListener(this);
    server->connect("127.0.0.1", 8888);

    current_state = WAIT_VEHICLE;
    current_id_player = 0;
    current_id_vehicle = 0;
    current_vehicle = 0;
    controls = 0;

    arrows_view = new ArrowsView(&view_list);
    stat_view = new StatView(&players);
    speedometer_view = new SpeedometerView(&players);

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
            bool isVehicle = class_object == GameObjectType::VEHICLE;
            int type_object = protocol->nextInt();
            Vector2D position;
            position.x = protocol->nextDouble();
            position.y = protocol->nextDouble();
            /*if (isVehicle) {
                Console::print(QString("Vehicle: ") + QVariant(position.x).toString()
                               + QString(",") + QVariant(position.y).toString());
            }/**/
            double rotation = protocol->nextDouble();
            WorkView* object = WorkView::findById(id_object);
            WorkView* parent = WorkView::findById(id_parent);
            if (object == 0)
            {
                if (class_object == GameObjectType::TURRET)
                {
                    object = new WorkView(id_object, class_object, type_object);
                    parent->addChild(object);

                }
                else
                {
                    object = new WorkView(id_object, class_object, type_object);
                    view_list.push_back(object);
                }
            }
            object->setPosition(position);
            object->setRotationZ(rotation);
        }
        else if (action == PLAYER_STAT)
        {
            int id_player = protocol->nextInt();
            int count_kills = protocol->nextInt();
            int count_dieds = protocol->nextInt();
            int health = protocol->nextInt();
            double speed = protocol->nextDouble();
            double spins = protocol->nextDouble();
            std::map<int, Player*>::iterator i = players.find(id_player);
            if (i != players.end())
            {
                (*i).second->count_kills = count_kills;
                (*i).second->count_dieds = count_dieds;
                (*i).second->health = health;
                (*i).second->speed = speed;
                (*i).second->spins = spins;
            }
        }
        else if (action == AUTH)
        {
            current_id_player = protocol->nextInt();
            Console::print(QString("Current Player #") + QVariant(current_id_player).toString());
            Player* player = new Player();
            player->id_player = current_id_player;
            players[current_id_player] = player;
        }
        else if (action == LOGIN)
        {
            int id_player = protocol->nextInt();
            if (id_player != current_id_player)
            {
                Console::print(QString("Player #") + QVariant(id_player).toString() + " logged IN");
            }
            Player* player = new Player();
            player->id_player = id_player;
            players[id_player] = player;
        }
        else if (action == LOGOUT)
        {
            int id_player = protocol->nextInt();
            if (id_player != current_id_player)
            {
                Console::print(QString("Player #") + QVariant(id_player).toString() + " logged OUT");
            }
            std::map<int, Player*>::iterator i = players.find(id_player);
            if (i != players.end())
            {
                delete (*i).second;
                players.erase(i);
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
            WorkView* obj = WorkView::findById(id_object);
            if (obj != 0)
            {
                if (current_id_vehicle == obj->id_object)
                {
                    Console::print("I am dead");
                    current_state = WAIT_VEHICLE;
                    current_vehicle = 0;
                    current_id_vehicle = 0;
                    delete controls;
                    controls = 0;
                }
                obj->valid = false;
            }
        }
    }
}

void GameplayState::render(const RenderData &render_data)
{
    Matrix camera_transform = Camera::gi()->getTransform();
    for (int i = 0; i < view_list.size(); ++i)
    {
        if (view_list[i]->valid)
        {
            view_list[i]->render(render_data.render2d, camera_transform, render_data.new_tick, render_data.interpolation);
        }
        else
        {
            unused_view_list.push_back(view_list[i]);
            view_list[i] = view_list[view_list.size() - 1];
            view_list.pop_back();
            --i;
        }
    }
    if (current_state == INITED)
    {
        Camera::gi()->setPosition(current_vehicle->getPosition());
    }

    arrows_view->render(render_data.render2d, Matrix(), render_data.new_tick, render_data.interpolation);
    stat_view->current_player_id = current_id_player;
    stat_view->render(render_data.render2d, Matrix(), render_data.new_tick, render_data.interpolation);
    speedometer_view->current_player_id = current_id_player;
    speedometer_view->render(render_data.render2d, Matrix(), render_data.new_tick, render_data.interpolation);
}

void GameplayState::tick(double dt)
{
    for (int i = 0; i < unused_view_list.size(); ++i)
    {
        delete unused_view_list[i];
    }
    unused_view_list.clear();
    if (current_id_vehicle != 0)
    {
        if (current_state == NEED_INIT_VEHICLE)
        {
            WorkView* model = WorkView::findById(current_id_vehicle);
            if (model != 0)
            {
                current_vehicle = model;
                controls = new UIController(model);
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
    for (int i = 0; i < unused_view_list.size(); ++i)
    {
        delete unused_view_list[i];
    }
    for (int i = 0; i < view_list.size(); ++i)
    {
        delete view_list[i];
    }

    delete arrows_view;
    delete stat_view;
    delete speedometer_view;

    Keyboard::gi()->removeEventListener(this);
    Mouse::gi()->removeEventListener(this);

    server->deleteLater();
    delete server;
}

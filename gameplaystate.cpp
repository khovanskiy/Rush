#include "gameplaystate.h"

#include "thread.h"
#include "random.h"
#include "gameobjectevent.h"

std::map<int, WorkView*> WorkView::cache_work;

void GameplayState::init()
{
    server = new NetworkServer();
    server->addEventListener(this);
    server->connect("127.0.0.1", 560);

    current_state = WAIT_VEHICLE;
    current_id_player = 0;
    current_id_vehicle = 0;
    current_vehicle = 0;
    controls = 0;

    arrows_view = new ArrowsView(&view_list);

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
            WorkView* object = WorkView::findById(id_object);
            WorkView* parent = WorkView::findById(id_parent);
            if (object != 0)
            {
                if (class_object != GameObjectType::TERRAIN)
                {
                    object->setPosition(position);
                    object->setRotationZ(rotation);
                }
            }
            else
            {
                if (class_object == GameObjectType::TURRET)
                {
                    WorkView* view = new WorkView(id_object, class_object, type_object);
                    parent->addChild(view);
                }
                else
                {
                    WorkView* view = new WorkView(id_object, class_object, type_object);
                    view_list.push_back(view);
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
    for (int i = 0; i < unused_view_list.size(); ++i)
    {
        delete unused_view_list[i];
    }
    unused_view_list.clear();
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
}

void GameplayState::tick(double dt)
{
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
    Keyboard::gi()->removeEventListener(this);
    Mouse::gi()->removeEventListener(this);

    server->deleteLater();
    delete server;
}

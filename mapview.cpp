#include "mapview.h"

MapView::MapView(GameWorld* world)
{
    this->world = world;
    world->addEventListener(this);
    std::vector<GameModelObject*> result = world->getInners();
    Console::print("Objects` count");
    Console::print(result.size());
    for (int i = 0; i < result.size(); ++i)
    {
        createObject(result[i]);
    }
}

void MapView::update()
{
    for (int i = 0; i < unused.size(); ++i)
    {
        delete unused[i];
    }
    unused.clear();
    for (int i = 0; i < list.size(); ++i)
    {
        if (!list[i]->isValid())
        {
            unused.push_back(list[i]);
            Stage::gi()->removeChild(list[i]);
            list[i] = list[list.size() - 1];
            list.pop_back();
            --i;
        }
    }
}

MapView::~MapView()
{
    for (int i = 0; i < unused.size(); ++i)
    {
        delete unused[i];
    }
    for (int i = 0; i < list.size(); ++i)
    {
        Stage::gi()->removeChild(list[i]);
        delete list[i];
    }
    Console::print("MapView is deleted");
}

void MapView::createObject(GameModelObject *go)
{
    switch (go->getFamilyId())
    {
    case GameObjectType::VEHICLE:
    {
        GameViewObject* view = new VehicleView(static_cast<Vehicle*>(go));
        view->addEventListener(this);
        list.push_back(view);

        Stage::gi()->addChild(view);
    } break;
    case GameObjectType::BULLET:
    {
        GameViewObject* view = new BulletView(static_cast<Bullet*>(go));
        view->addEventListener(this);
        list.push_back(view);

        Stage::gi()->addChild(view);
    } break;
    }
}

void MapView::Invoke(const Event &event)
{
    if (event.type == GameObjectEvent::ADDED_OBJECT)
    {
        const GameObjectEvent* e = static_cast<const GameObjectEvent*>(&event);
        createObject(e->subject);
    }
}

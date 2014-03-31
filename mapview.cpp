#include "mapview.h"

MapView::MapView(GameWorld* world)
{
    this->world = world;
    world->addEventListener(this);
    std::vector<GameModelObject*> result = world->getInners();
    Console::print(result.size());
    for (int i = 0; i < result.size(); ++i)
    {
        createObject(result[i]);
    }
}

void MapView::createObject(GameModelObject *go)
{
    Console::print("object");
    Console::print(go->getFamilyId());
    switch (go->getFamilyId())
    {
    case GameObjectType::VEHICLE:
    {
        Console::print("create vehicle");
        GameViewObject* view = new VehicleView(static_cast<Vehicle*>(go));
        view->addEventListener(this);
        list.push_back(view);

        Stage::gi()->addChild(view);
    } break;
    case GameObjectType::BULLET:
    {
        Console::print("create bullet");
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
    else if (event.type == Event::REMOVED_FROM_STAGE)
    {
        GameViewObject* view = static_cast<GameViewObject*>(event.target);
        list.erase(std::remove(list.begin(), list.end(), view));
        Stage::gi()->removeChild(view);
    }
}

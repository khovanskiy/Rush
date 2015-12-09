#include "gamemodelobject.h"
#include "gameobjectevent.h"

std::map<int, GameModelObject*> GameModelObject::registry;

GameModelObject::~GameModelObject()
{
    registry.erase(my_id);
}

GameModelObject::GameModelObject(int my_id)
{
    this->valid = true;
    this->my_id = my_id;
    this->type_object = 0;
    registry[my_id] = this;
}

GameModelObject* GameModelObject::findById(int id)
{
    std::map<int, GameModelObject*>::iterator i = registry.find(id);
    if (i != registry.end())
    {
        return (*i).second;
    }
    else
    {
        return 0;
    }
}

bool GameModelObject::isValid()
{
    return valid;
}

void GameModelObject::invalidate()
{
    if (valid)
    {
        valid = false;
        dispatchEvent(Event(this, Event::INVALIDATE));
    }
}

void GameModelObject::add(GameModelObject *go)
{
    inners.push_back(go);
    dispatchEvent(GameObjectEvent(this, GameObjectEvent::ADDED_OBJECT, go));
}

const std::vector<GameModelObject*>& GameModelObject::getInners() const
{
    return inners;
}

void GameModelObject::tick(double dt)
{
    for (int i = 0; i < inners.size(); ++i)
    {
        if (inners[i]->isValid())
        {
            inners[i]->tick(dt);
        }
        else
        {
            inners[i] = inners[inners.size() - 1];
            inners.pop_back();
            --i;
        }
    }
}

GameObjectType GameModelObject::getFamilyId()
{
    return GameObjectType::UNKNOWN;
}

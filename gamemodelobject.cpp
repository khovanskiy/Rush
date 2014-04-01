#include "gamemodelobject.h"
#include "console.h"

GameModelObject::~GameModelObject()
{

}

GameModelObject::GameModelObject(__int64 id)
{
    this->valid = true;
}

GameModelObject::GameModelObject()
{
    this->valid = true;
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

#include "gamemodelobject.h"
#include "console.h"

GameModelObject::~GameModelObject()
{

}

GameModelObject::GameModelObject(__int64 id)
{
    this->valid = true;
    uses_count = 0;
}

GameModelObject::GameModelObject()
{
    this->valid = true;
    uses_count = 0;
}

bool GameModelObject::isValid()
{
    return valid;
}

void GameModelObject::invalidate()
{
    if (valid)
    {
        Console::print("i am invalidate");
        Console::print(this);
        valid = false;
        dispatchEvent(Event(this, Event::INVALIDATE));
    }
}

void GameModelObject::add(GameModelObject *go)
{
    ++go->uses_count;
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
            Console::print("must delete");
            GameModelObject* go = inners[i];
            --go->uses_count;
            inners[i] = inners[inners.size() - 1];
            inners.pop_back();
            if (!go->uses_count)
            {
                delete go;
            }
        }
    }
}

GameObjectType GameModelObject::getFamilyId()
{
    return GameObjectType::UNKNOWN;
}

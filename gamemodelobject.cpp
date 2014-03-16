#include "gamemodelobject.h"
#include "console.h"

std::map<__int64, GameModelObject*> GameModelObject::table;

GameModelObject::~GameModelObject()
{
    erase(this->my_id);
}

GameModelObject::GameModelObject(__int64 id)
{
    //insert(id, this);
    this->my_id = 0;
    this->valid = true;
}

GameModelObject::GameModelObject()
{
    this->my_id = 0;
    this->valid = true;
}

bool GameModelObject::isValid()
{
    return valid;
}

void GameModelObject::invalidate()
{
    if (this->valid)
    {
        dispatchEvent(Event(this, Event::INVALIDATE));
        this->valid = false;
    }
}

void GameModelObject::add(GameModelObject *go)
{

}

void GameModelObject::update(double dt)
{

}

__int64 GameModelObject::getId()
{
    return this->my_id;
}

void GameModelObject::insert(__int64 id, const GameModelObject * obj)
{
    this->my_id = id;
    table[id] = this;
}

void GameModelObject::erase(__int64 id)
{
    std::map<__int64, GameModelObject*>::iterator i = table.find(id);
    if (i != table.end())
    {
        table.erase(i);
    }
}

void GameModelObject::setId(__int64 id)
{
    if (findById(id) == 0)
    {
        erase(id);
        erase(my_id);
        insert(id, this);
    }
}

GameModelObject* GameModelObject::findById(__int64 id)
{
    GameModelObject* result = 0;
    std::map<__int64, GameModelObject*>::iterator i = table.find(id);
    if (i != table.end())
    {
        result = i->second;
    }
    return result;
}

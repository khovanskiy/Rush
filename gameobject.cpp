#include "gameobject.h"

std::map<__int64, GameObject*> GameObject::table;

GameObject::GameObject(__int64 id)
{
    insert(id, this);
}

GameObject::~GameObject()
{
    erase(this->my_id);
}

__int64 GameObject::getId()
{
    return this->my_id;
}

void GameObject::insert(__int64 id, const GameObject * obj)
{
    this->my_id = id;
    table[id] = this;
}

void GameObject::erase(__int64 id)
{
    std::map<__int64, GameObject*>::iterator i = table.find(id);
    if (i != table.end())
    {
        table.erase(i);
    }
}

void GameObject::setId(__int64 id)
{
    if (findById(id) == 0)
    {
        erase(id);
        erase(my_id);
        insert(id, this);
    }
}

GameObject* GameObject::findById(__int64 id)
{
    GameObject* result = 0;
    std::map<__int64, GameObject*>::iterator i = table.find(id);
    if (i != table.end())
    {
        result = i->second;
    }
    return result;
}

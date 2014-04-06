#include "gameobjectevent.h"

const QString GameObjectEvent::ADDED_OBJECT = "addedObject";
const QString GameObjectEvent::UPDATED_OBJECT = "updatedObject";
const QString GameObjectEvent::REMOVED_OBJECT = "removedObject";
const QString GameObjectEvent::AUTHORIZED = "authorized";

GameObjectEvent::GameObjectEvent(EventDispatcher* target, QString type, GameModelObject* subject) : Event(target, type)
{
    this->subject = subject;
}

GameObjectEvent::GameObjectEvent(EventDispatcher* target, QString type, const Vector2D& position) : Event(target, type)
{
    this->position = position;
}

GameObjectEvent::GameObjectEvent(EventDispatcher* target, QString type, int id_object, GameObjectType go_type) : Event(target, type)
{
    this->id_object = id_object;
    this->class_object = go_type;
}

GameObjectEvent::GameObjectEvent(EventDispatcher* target, QString type) : Event(target, type)
{
    id_player = 0;
    id_object = 0;
    id_parent = 0;
    class_object = (GameObjectType)5;
    type_object = 0;
    rotation = 0;
}

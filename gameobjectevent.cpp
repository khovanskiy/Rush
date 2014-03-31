#include "gameobjectevent.h"

const QString GameObjectEvent::ADDED_OBJECT = "addedObject";
const QString GameObjectEvent::REMOVED_OBJECT = "removedObject";

GameObjectEvent::GameObjectEvent(EventDispatcher* target, QString type, GameModelObject* subject) : Event(target, type)
{
    this->subject = subject;
}

GameObjectEvent::GameObjectEvent(EventDispatcher* target, QString type, const Vector2D& position) : Event(target, type)
{
    this->v = position;
}

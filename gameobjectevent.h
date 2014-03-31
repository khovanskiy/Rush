#ifndef GAMEOBJECTEVENT_H
#define GAMEOBJECTEVENT_H

#include "event.h"
#include "vector2d.h"

class GameModelObject;

class GameObjectEvent : public Event
{
public:
    static const QString ADDED_OBJECT;
    static const QString REMOVED_OBJECT;

    GameObjectEvent(EventDispatcher*, QString, GameModelObject* = 0);
    GameObjectEvent(EventDispatcher*, QString, const Vector2D& position);
    GameModelObject* subject;
    Vector2D v;
};

#endif // GAMEOBJECTEVENT_H

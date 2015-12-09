#ifndef GAMEOBJECTEVENT_H
#define GAMEOBJECTEVENT_H

#include "common/event.h"
#include "common/vector2d.h"
#include "common/AccelerationState.h"
#include "common/gamemodelobject.h"

class GameModelObject;

class GameObjectEvent : public Event
{
public:
    static const QString ADDED_OBJECT;
    static const QString REMOVED_OBJECT;
    static const QString UPDATED_OBJECT;
    static const QString AUTHORIZED;

    GameObjectEvent(EventDispatcher*, QString, GameModelObject*);
    GameObjectEvent(EventDispatcher*, QString, const Vector2D& position);
    GameObjectEvent(EventDispatcher*, QString, int, GameObjectType);
    GameObjectEvent(EventDispatcher*, QString);
    GameModelObject* subject;
    int id_player;
    int id_object;
    int id_parent;
    Vector2D position;
    double rotation;
    GameObjectType class_object;
    int type_object;
    bool shooting;
    AccelerationState acc_state;
};

#endif // GAMEOBJECTEVENT_H

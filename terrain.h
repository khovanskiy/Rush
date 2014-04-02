#ifndef STATICGAMEOBJECT_H
#define STATICGAMEOBJECT_H

#include "gamemodelobject.h"
#include "transformableobject.h"

class Terrain : public GameModelObject, public TransformableObject
{
public:
    Terrain();
    int type;
    GameObjectType getFamilyId();
};

#endif // STATICGAMEOBJECT_H

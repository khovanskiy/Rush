#ifndef TERRAIN_H
#define TERRAIN_H

#include "gamemodelobject.h"
#include "transformableobject.h"

class Terrain : public GameModelObject, public TransformableObject
{
public:
    Terrain(int id);
    int type;
    GameObjectType getFamilyId();
};

#endif // TERRAIN_H

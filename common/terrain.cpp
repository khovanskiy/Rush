#include "terrain.h"

Terrain::Terrain(int id) : GameModelObject(id)
{
    type = 0;
    setSize(Vector2D(100,100));
}

GameObjectType Terrain::getFamilyId()
{
    return GameObjectType::TERRAIN;
}

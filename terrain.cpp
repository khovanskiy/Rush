#include "terrain.h"

Terrain::Terrain(int id) : GameModelObject(id)
{
    type = 0;
    setSize(Vector2D(30,30));
}

GameObjectType Terrain::getFamilyId()
{
    return GameObjectType::TERRAIN;
}

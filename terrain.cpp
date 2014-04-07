#include "terrain.h"

Terrain::Terrain(int id) : GameModelObject(id)
{
    type = 0;
    setSize(Vector2D(300,285));
}

GameObjectType Terrain::getFamilyId()
{
    return GameObjectType::TERRAIN;
}

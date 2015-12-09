#include "terrainview.h"

TerrainView::TerrainView(Terrain* static_go)
{
    this->static_go = static_go;

    texture = new Bitmap();
    switch (static_go->type)
    {
    default:
    {
        texture->load("DATA\\Textures\\Terrains\\1.jpg");
    } break;
    }
    texture->setSize(static_go->getSize());
    this->setX(static_go->getPosition().x);
    this->setY(static_go->getPosition().y);
    addChild(texture);
}

TerrainView::~TerrainView()
{
    delete texture;
}

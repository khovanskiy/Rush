#ifndef STATICGAMEOBJECTVIEW_H
#define STATICGAMEOBJECTVIEW_H

#include "terrain.h"
#include "gameviewobject.h"
#include "client/bitmap.h"

class TerrainView : public GameViewObject
{
public:
    TerrainView(Terrain* static_go);
    virtual ~TerrainView();
private:
    Terrain* static_go;
    Bitmap* texture;
};

#endif // STATICGAMEOBJECTVIEW_H

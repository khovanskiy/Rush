#ifndef STATICGAMEOBJECTVIEW_H
#define STATICGAMEOBJECTVIEW_H

#include "../common/terrain.h"
#include "gameviewobject.h"
#include "bitmap.h"

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

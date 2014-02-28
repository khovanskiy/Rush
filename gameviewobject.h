#ifndef GAMEVIEWOBJECT_H
#define GAMEVIEWOBJECT_H

#include "sprite.h"
#include "bitmap.h"
#include "vector2d.h"
#include "gamemodelobject.h"

class GameViewObject : public Sprite
{
public:
    GameViewObject();
    ~GameViewObject();
protected:
    int m_to_px;
};

#endif // GAMEVIEWOBJECT_H

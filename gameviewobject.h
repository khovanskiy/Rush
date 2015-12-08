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
    bool isValid();
    virtual void invalidate();
protected:
    int m_to_px;
    bool valid;
};

#endif // GAMEVIEWOBJECT_H

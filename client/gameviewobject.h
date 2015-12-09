#ifndef GAMEVIEWOBJECT_H
#define GAMEVIEWOBJECT_H

#include "sprite.h"
#include "../common/vector2d.h"
#include "../common/gamemodelobject.h"

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

#ifndef TURRETVIEW_H
#define TURRETVIEW_H

#include "gameviewobject.h"
#include "sprite.h"
#include "bitmap.h"

#include "turret.h"

class TurretView : public GameViewObject
{
public:
    TurretView(Turret* turret);
    virtual ~TurretView();
    virtual void render(QPainter *, const Matrix &, bool, float);
protected:
    Bitmap* body;
    Turret* turret;
};

#endif // TURRETVIEW_H

#ifndef TURRETVIEW_H
#define TURRETVIEW_H

#include "gameviewobject.h"
#include "sprite.h"

#include "turret.h"
#include "client/bitmap.h"

class TurretView : public GameViewObject, public EventHandler
{
public:
    TurretView(Turret* turret);
    virtual ~TurretView();
    void Invoke(const Event &);
    virtual void render(QPainter *, const Matrix &, bool, float);
protected:
    Bitmap* body;
    Turret* turret;
};

#endif // TURRETVIEW_H

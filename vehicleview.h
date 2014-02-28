#ifndef VEHICLEVIEW_H
#define VEHICLEVIEW_H

#include "gameviewobject.h"
#include "vehicle.h"
#include "bitmap.h"
#include "sprite.h"

#include "turretview.h"

class VehicleView : public GameViewObject
{
public:
    VehicleView(Vehicle* vehicle);
    virtual ~VehicleView();
    virtual void render(QPainter *, const Matrix &, bool, float);
protected:
    Vehicle* vehicle;
    Bitmap* body;
    std::vector<TurretView*> turrets;
};

#endif // VEHICLEVIEW_H

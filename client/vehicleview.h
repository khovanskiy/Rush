#ifndef VEHICLEVIEW_H
#define VEHICLEVIEW_H

#include "gameviewobject.h"
#include "../common/vehicle.h"
#include "sprite.h"

#include "turretview.h"
#include "bitmap.h"

class VehicleView : public GameViewObject, public EventHandler
{
public:
    VehicleView(Vehicle* vehicle);
    virtual ~VehicleView();
    virtual void render(QPainter *, const Matrix &, bool, float);
    virtual void Invoke(const Event &event);
protected:
    Vehicle* vehicle;
    Bitmap* body;
    std::vector<TurretView*> turrets;
};

#endif // VEHICLEVIEW_H

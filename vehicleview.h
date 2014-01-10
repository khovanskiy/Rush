#ifndef VEHICLEVIEW_H
#define VEHICLEVIEW_H

#include "vehicle.h"
#include "sprite.h"

class VehicleView : public Sprite
{
public:
    VehicleView(Vehicle* vehicle);
protected:
    Vehicle* vehicle;
};

#endif // VEHICLEVIEW_H

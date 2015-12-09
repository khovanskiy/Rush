#ifndef UIVEHICLECONTROLLER_H
#define UIVEHICLECONTROLLER_H

#include "../common/vehicle.h"

#include "keyboard.h"
#include "mouse.h"

class UIVehicleController : public EventDispatcher, public EventHandler
{
public:
    UIVehicleController(Vehicle* vehicle);
    virtual ~UIVehicleController();
    void Invoke(const Event &event);
private:
    Vehicle* vehicle;
};

#endif // UIVEHICLECONTROLLER_H

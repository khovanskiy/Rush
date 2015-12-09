#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include "../common/vehicle.h"
#include "camera.h"

class CameraController
{
public:
    CameraController(Vehicle* v);
    void update();
    virtual ~CameraController();
private:
    Vehicle* v;
};

#endif // CAMERACONTROLLER_H

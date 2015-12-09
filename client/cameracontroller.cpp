#include "cameracontroller.h"

CameraController::CameraController(Vehicle* v)
{
    this->v = v;
}

CameraController::~CameraController()
{

}

void CameraController::update()
{
    Camera::gi()->setPosition(v->getCoordinates());
}

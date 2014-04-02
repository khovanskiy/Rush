#include "vehicleview.h"

VehicleView::VehicleView(Vehicle* vehicle)
{
    this->vehicle = vehicle;
    vehicle->addEventListener(this);

    body = new Bitmap();
    body->load("DATA\\Textures\\Vehicles\\dodge.png");
    //body->setInter(true);
    body->setRSPointCenter();
    body->setWidth(vehicle->getWidth());
    body->setHeight(vehicle->getHeight());

    this->addChild(body);

    for (int i = 0; i < vehicle->turrets.size(); ++i)
    {
        TurretView* turret = new TurretView(vehicle->turrets[i]);
        turrets.push_back(turret);

        this->addChild(turret);
    }
}

void VehicleView::Invoke(const Event &event)
{
    if (event.type == Event::INVALIDATE)
    {
        Console::print("get invalidate from vehicle");
        invalidate();
    }
}

void VehicleView::render(QPainter *render2d, const Matrix &base, bool new_frame, float interpolation)
{
    this->setX(vehicle->getCoordinates().x);
    this->setY(vehicle->getCoordinates().y);
    this->setRotationZ(vehicle->getAngle());
    GameViewObject::render(render2d, base, new_frame, interpolation);
}

VehicleView::~VehicleView()
{
    Console::print("Vehicle View is deleted");
    vehicle->removeEventListener(this);
    for (int i = 0; i < turrets.size(); ++i)
    {
        delete turrets[i];
    }
    delete body;
}

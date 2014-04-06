#include "vehicleview.h"

#include "gameobjectevent.h"

VehicleView::VehicleView(Vehicle* vehicle)
{
    this->vehicle = vehicle;
    vehicle->addEventListener(this);

    body = new Bitmap();
    switch (vehicle->vehicle_type)
    {
    case 0:
    {
        body->load("DATA\\Textures\\Vehicles\\dodge.png");
    } break;
    case 1:
    {
        body->load("DATA\\Textures\\Vehicles\\ferrari.png");
    } break;
    case 2:
    {
        body->load("DATA\\Textures\\Vehicles\\ford-f-150.png");
    } break;
    }
    body->setInter(true);
    this->setInter(true);
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
        vehicle->removeEventListener(this);
        vehicle = 0;
        invalidate();
    }
    else if (event.type == GameObjectEvent::ADDED_OBJECT)
    {
        const GameObjectEvent* e = static_cast<const GameObjectEvent*>(&event);
        Turret* turret = static_cast<Turret*>(e->subject);

        TurretView* turret_view = new TurretView(turret);
        turrets.push_back(turret_view);

        this->addChild(turret_view);
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
    if (vehicle)
    {
        vehicle->removeEventListener(this);
    }
    for (int i = 0; i < turrets.size(); ++i)
    {
        delete turrets[i];
    }
    delete body;
    Console::print("Vehicle View is deleted");
}

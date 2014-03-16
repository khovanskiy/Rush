#include "vehicleview.h"

VehicleView::VehicleView(Vehicle* vehicle)
{
    this->vehicle = vehicle;
    vehicle->addEventListener(this);

    body = new Bitmap();
    body->load("DATA\\Textures\\Vehicles\\dodge.png");
    body->setInter(true);
    body->setRSPointCenter();
    body->setWidth(m_to_px * vehicle->getWidth());
    body->setHeight(m_to_px * vehicle->getHeight());

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
        for (int i = 0; i < turrets.size(); ++i)
        {
            TurretView* turret = turrets[i];
            this->removeChild(turret);
            delete turret;
        }
        turrets.clear();
        Console::print("invalidate");
    }
}

void VehicleView::render(QPainter *render2d, const Matrix &base, bool new_frame, float interpolation)
{
    if (vehicle != 0)
    {
        this->setX(m_to_px * vehicle->getCoordinates().x);
        this->setY(m_to_px * vehicle->getCoordinates().y);
        this->setRotationZ(vehicle->getAngle());

        Sprite::render(render2d, base, new_frame, interpolation);
    }
}

VehicleView::~VehicleView()
{
    for (int i = 0; i < turrets.size(); ++i)
    {
        TurretView* turret = turrets[i];
        this->removeChild(turret);
        delete turret;
    }
    turrets.clear();

    this->removeChild(body);
    delete body;
}

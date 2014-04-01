#include "turretview.h"

TurretView::TurretView(Turret* turret)
{
    this->turret = turret;
    body = new Bitmap();
    body->load("DATA\\Textures\\Turrets\\nailgun.png");
    body->setInter(true);
    body->setRSPointCenter();

    body->setWidth(m_to_px * turret->getWidth());
    body->setHeight(m_to_px * turret->getHeight());

    this->addChild(body);
}

TurretView::~TurretView()
{
    delete body;
    Console::print("TurretView is deleted");
}

void TurretView::render(QPainter *render2d, const Matrix &base, bool new_frame, float interpolation)
{
    //if (valid)
    {
        this->setX(m_to_px * turret->getCoordinates().x);
        this->setY(m_to_px * turret->getCoordinates().y);
        this->setRotationZ(turret->getAngle());

        GameViewObject::render(render2d, base, new_frame, interpolation);
    }
}
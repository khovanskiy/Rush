#include "bulletview.h"

BulletView::BulletView(Bullet* bullet)
{
    this->bullet = bullet;
    bullet->addEventListener(this);

    body = new Bitmap();
    body->load("DATA\\Textures\\Bullets\\missile.png");
    body->setInter(true);
    body->setRSPointCenter();

    body->setWidth(m_to_px * bullet->getWidth());
    body->setHeight(m_to_px * bullet->getHeight());

    this->addChild(body);
}

BulletView::~BulletView()
{
    Console::print("Deleted bullet view");
    bullet->removeEventListener(this);
    delete body;
}

void BulletView::Invoke(const Event &event)
{
    if (event.type == Event::INVALIDATE)
    {
        invalidate();
    }
}


void BulletView::render(QPainter *render2d, const Matrix &base, bool new_frame, float interpolation)
{
    //if (valid)
    {
        this->setX(m_to_px * bullet->getCoordinates().x);
        this->setY(m_to_px * bullet->getCoordinates().y);
        this->setRotationZ(bullet->getAngle());

        GameViewObject::render(render2d, base, new_frame, interpolation);
    }
}

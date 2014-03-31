#include "bulletview.h"

BulletView::BulletView(Bullet* bullet)
{
    this->bullet = bullet;
    bullet->addEventListener(this);

    body = new Bitmap();
    body->load("DATA\\Textures\\Bullets\\missile.png");
    body->setInter(true);
    body->setRSPointCenter();

    Console::print("Bullet size");
    //Console::print(bullet->getWidth());
    //Console::print(bullet->getHeight());
    body->setWidth(m_to_px * 1);
    body->setHeight(m_to_px * 1);

    this->addChild(body);
}

BulletView::~BulletView()
{
    this->removeChild(body);
    delete body;
}

void BulletView::Invoke(const Event &event)
{
    if (event.type == Event::INVALIDATE)
    {
        //Console::print("invalidate bullet view");
        dispatchEvent(Event(this, Event::REMOVED_FROM_STAGE));
    }
}


void BulletView::render(QPainter *render2d, const Matrix &base, bool new_frame, float interpolation)
{
    this->setX(m_to_px * bullet->getCoordinates().x);
    this->setY(m_to_px * bullet->getCoordinates().y);
    this->setRotationZ(bullet->getAngle());

    Sprite::render(render2d, base, new_frame, interpolation);
}

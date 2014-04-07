#include "obstacleview.h"

ObstacleView::ObstacleView(Obstacle* obstacle)
{
    this->obstacle = obstacle;
    obstacle->addEventListener(this);

    body = new Bitmap();
    switch (obstacle->obstacle_type)
    {
    case 0:
    {
        body->load("DATA\\Textures\\Obstacles\\stone_wall.png");
    } break;
    }
    body->setRSPointCenter();
    body->setWidth(obstacle->getWidth());
    body->setHeight(obstacle->getHeight());
    addChild(body);
}

ObstacleView::~ObstacleView()
{
    if (obstacle)
    {
        obstacle->removeEventListener(this);
    }
    delete body;
}

void ObstacleView::Invoke(const Event &event)
{
    if (event.type == Event::INVALIDATE)
    {
        obstacle->removeEventListener(this);
        obstacle = 0;
        invalidate();
    }
}

void ObstacleView::render(QPainter *render2d, const Matrix &base, bool new_frame, float interpolation)
{
    this->setX(obstacle->getCoordinates().x);
    this->setY(obstacle->getCoordinates().y);
    this->setRotationZ(obstacle->getAngle());
    GameViewObject::render(render2d, base, new_frame, interpolation);
}

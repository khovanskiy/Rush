#include "gameviewobject.h"
#include <QCoreApplication>
#include "console.h"

GameViewObject::GameViewObject(QString path,
                               std::vector<GameViewObject*> inner_objects,
                               GameModelObject* game_model_object)
    : path(path), inner_objects(inner_objects),
      game_model_object(game_model_object)
{
    this->bitmap = new Bitmap();
    bitmap->load(QCoreApplication::applicationDirPath() + path);
    bitmap->setRSPointCenter();
    bitmap->setWidth(game_model_object->getWidth());
    bitmap->setHeight(game_model_object->getHeight());
}

GameViewObject::~GameViewObject()
{
    delete bitmap;
    for (auto i = inner_objects.begin(); i != inner_objects.end(); i++)
    {
        delete *i;
    }
}

void GameViewObject::invalidate()
{
    game_model_object->invalidate();
}

bool GameViewObject::isValid()
{
    return (game_model_object != 0) && (game_model_object->isValid());
}

void GameViewObject::update(double scale, Vector2D d_r, double d_angle, Vector2D center)
{
    Vector2D r = game_model_object->getCenter();
    r.add(d_r);
    r.rotate(d_angle);
    Vector2D c = center;
    c.div(scale);
    r.add(c);
    bitmap->setX(scale * r.x);
    bitmap->setY(scale * r.y);
    double angle = game_model_object->getAngle() + d_angle;
    bitmap->setRotationZ(angle);
    bitmap->setWidth(scale * game_model_object->getWidth());
    bitmap->setHeight(scale * game_model_object->getHeight());
    for (auto i = inner_objects.begin(); i != inner_objects.end(); i++)
    {
        (*i)->update(scale, d_r, d_angle, center);
    }
}


Bitmap* GameViewObject::getBitmap()
{
    return this->bitmap;
}


std::vector<GameViewObject*> GameViewObject::getInnerObjects()
{
    return this->inner_objects;
}

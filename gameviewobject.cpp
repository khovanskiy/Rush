#include "gameviewobject.h"

GameViewObject::GameViewObject(QString path, double width, double height,
                               Vector2D r, Vector2D v, double angle, double angular_speed,
                               std::vector<GameViewObject*> inner_objects)
    : path(path), width(width), height(height), r(r), v(v), angle(angle), angular_speed(angular_speed),
      inner_objects(inner_objects)
{
    this->bitmap = new Bitmap();
    bitmap->load(QCoreApplication::applicationDirPath() + path);
    bitmap->setRSPointCenter();
    bitmap->setWidth(width);
    bitmap->setHeight(height);
    bitmap->setRotationZ(angle);
}

GameViewObject::~GameViewObject()
{
    for (auto i = inner_objects.begin(); i != inner_objects.end(); i++)
    {
        delete *i;
    }
    delete bitmap;
}



#ifndef GAMEVIEWOBJECT_H
#define GAMEVIEWOBJECT_H
#include "bitmap.h"
#include "vector2d.h"
#include <QCoreApplication>

class GameViewObject
{
    int id;
    Bitmap* bitmap;
    QString path;
    double width, height;
    Vector2D local_r, local_v;
    double angle, angular_speed;

    Vector2D global_r;
    double global_angle;

    std::vector<int> inner_ids;

public:
    GameViewObject(QString path, double width, double height,
                   Vector2D r, Vector2D v, double angle, double angular_speed,
                   std::vector<GameViewObject*> inner_objects);
    ~GameViewObject();

    void updateInfo(QString path, double width, double height,
                Vector2D r, Vector2D v, double angle, double angular_speed,
                std::vector<GameViewObject*> inner_objects);
    void tick(double dt);
    void update(double d_r, double d_angle, double scale, Vector2D center);
};

#endif // GAMEVIEWOBJECT_H

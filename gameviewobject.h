#ifndef GAMEVIEWOBJECT_H
#define GAMEVIEWOBJECT_H
#include "bitmap.h"
#include "vector2d.h"
#include "gamemodelobject.h"

class GameViewObject
{
    Bitmap* bitmap;
    QString path;
    double width, height;

    std::vector<GameViewObject*> inner_objects;
    GameModelObject* game_model_object;

public:
    GameViewObject(QString path,
                   std::vector<GameViewObject*> inner_objects,
                   GameModelObject* game_model_object);
    ~GameViewObject();

    void update(double scale, Vector2D d_r, double d_angle, Vector2D center);
    void invalidate();
    bool isValid();

    Bitmap* getBitmap();

    std::vector<GameViewObject*> getInnerObjects();
};

#endif // GAMEVIEWOBJECT_H

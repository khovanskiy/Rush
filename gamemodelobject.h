#ifndef GAMEMODELOBJECT_H
#define GAMEMODELOBJECT_H
#include "bitmap.h"
#include "physicsworld.h"
#include "physicsobjectfactory.h"

class GameModelObject
{
    std::vector<GameModelObject*> inner_objects;
    QString primary_type;
    QString secondary_type;
    double health;

    int id;
    Vector2D r, v;
    double angle, angular_speed;
    double width, height;

    Vector2D global_r;
    double global_angle;
    ObjectData* object_data;

public:

    GameModelObject(ObjectData* object_data);
    GameModelObject(int id, Vector2D r, Vector2D v,
                    double angle, double angular_speed,
                    QString primary_type, QString secondary_type,
                    double health, double width, double height,
                    std::vector<GameModelObject*> inner_objects);
    ~GameModelObject();
    std::vector<GameModelObject*> getInnerObjects();
    void update(double dt, Vector2D parent_r, double parent_angle);
    void invalidate();
    bool isValid();
    int getId();
    Vector2D getCenter();
    double getAngle();
    double getWidth();
    double getHeight();
    QString getPrimaryType();
    QString getSecondaryType();
    //QString serialize();
};

#endif // GAMEMODELOBJECT_H

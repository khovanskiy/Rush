#ifndef GAMEMODELOBJECT_H
#define GAMEMODELOBJECT_H
#include "bitmap.h"
#include "physicsworld.h"
#include "physicsobjectfactory.h"

class GameModelObject
{
    std::vector<int> inner_objects;
    QString primaryType;
    QString secondaryType;
    double health;

public:
    ObjectData* object_data;

    GameModelObject(ObjectData* object_data);

    std::vector<GameModelObject*> getInnerObjects();
    void update();
    //QString serialize();
};

#endif // GAMEMODELOBJECT_H

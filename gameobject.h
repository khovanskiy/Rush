#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "bitmap.h"
#include "physicsworld.h"
#include "physicsobjectfactory.h"

class GameObject
{
    std::vector<GameObject*> inner_objects;
    double health;

public:
    Bitmap* bitmap;
    ObjectData* object_data;

    GameObject(ObjectData* object_data);
    ~GameObject();

    void update(double scale, double angle, Vector2D dr, Vector2D center);
    std::vector<GameObject*> getInnerObjects();
};

#endif // GAMEOBJECT_H

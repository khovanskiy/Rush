#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "bitmap.h"
#include "physicsobject.h"
#include "vehicle.h"
#include "obstacle.h"

class GameObject
{
    std::vector<GameObject*> inner_objects;

public:
    Bitmap* bitmap;
    PhysicsObject* physics_object;

    GameObject(PhysicsObject* object);
    ~GameObject();

    void update(double scale, double angle, Vector2D dr, Vector2D center);
    std::vector<GameObject*> getInnerObjects();
};

#endif // GAMEOBJECT_H

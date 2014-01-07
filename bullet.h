#ifndef BULLET_H
#define BULLET_H
#include "physicsobject.h"

struct Bullet : public PhysicsObject
{
    int bullet_id;
    PhysicsObject* source;

    Bullet(Vector2D r, Vector2D speed, double mass, int bullet_id);

    void setSource(PhysicsObject* source);    
};

#endif // BULLET_H

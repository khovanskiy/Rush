#ifndef PHYSICSWORLD_H
#define PHYSICSWORLD_H
#include <vector>
#include "physicsobject.h"

struct ObjectData
{
    PhysicsObject* object;
    std::vector<Collision> collisions;

    ObjectData(PhysicsObject* object)
    {
        this->object = object;
    }

    ~ObjectData()
    {
        delete this->object;
    }
};

struct CollidingPair
{
    ObjectData* o1;
    ObjectData* o2;

    CollidingPair(ObjectData* o1, ObjectData* o2)
    {
        this->o1 = o1;
        this->o2 = o2;
    }
};

class PhysicsWorld
{
    PhysicsWorld(){};
    PhysicsWorld(PhysicsWorld const &);
    void operator=(PhysicsWorld const&);
    ~PhysicsWorld();

    std::vector<PhysicsObject*> new_objects;
    std::vector<CollidingPair> colliding_pairs;
    std::vector<CollidingPair> potentially_colliding;
    std::vector<ObjectData*> objects;

    void broadCollisionSearch(double dt);
    void yCollisionSearch(std::vector<std::pair<ObjectData*, AABB>> y_colliding);
    void addColliding(std::vector<std::pair<ObjectData*, AABB>> colliding);
    void narrowCollisionSearch(double dt);
    void collisionSolving(double dt);
    void changingStates(double dt);
    void integrating(double dt);

public:
    static PhysicsWorld& getInstance()
    {
        static PhysicsWorld instance;
        return instance;
    }

    void addObject(PhysicsObject* object);
    void removeObject(PhysicsObject* object);
    std::vector<ObjectData*> getObjectDatas();
    std::vector<PhysicsObject*> popNewObjects();
    void clear();
    void tick(double dt);
};

#endif // PHYSICSWORLD_H

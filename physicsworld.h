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
    Point2D center;

    CollidingPair(ObjectData* o1, ObjectData* o2, Point2D center)
        : center(center)
    {
        this->o1 = o1;
        this->o2 = o2;
    }
};

class PhysicsWorld
{
    PhysicsWorld()
    {
        this->closed = false;
    }
    PhysicsWorld(PhysicsWorld const &);
    void operator=(PhysicsWorld const&);
    ~PhysicsWorld();

    std::vector<PhysicsObject*> to_delete;
    std::vector<ObjectData*> new_objects;
    std::vector<CollidingPair> colliding_pairs;
    std::vector<std::pair<ObjectData*, ObjectData*>> potentially_colliding;
    std::vector<ObjectData*> objects;

    bool closed;

    void broadCollisionSearch();
    void xCollisionSearch(std::vector<std::pair<ObjectData*, AABB>> x_colliding, int iteration);
    void yCollisionSearch(std::vector<std::pair<ObjectData*, AABB>> y_colliding, int iteration);
    void addColliding(std::vector<std::pair<ObjectData*, AABB>> colliding);
    void narrowCollisionSearch();
    void collisionSolving();
    void collisionSearch();
    std::vector<PhysicsObject*> changingStates(double dt);
    void integrating(double dt);
    void addingObjects(std::vector<PhysicsObject*> const & n_objects);
    void deleteInvalidObjects();

public:
    static PhysicsWorld& gi()
    {
        static PhysicsWorld instance;
        return instance;
    }

    void addObject(PhysicsObject* object);
    void removeObject(PhysicsObject* object);
    std::vector<ObjectData*> getObjectDatas();
    std::vector<ObjectData*> popNewObjects();
    void clear();
    void tick(double dt);
    bool isClosed();
};

#endif // PHYSICSWORLD_H

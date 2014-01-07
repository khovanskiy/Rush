#include "physicsworld.h"
#include <algorithm>
#include "console.h"

typedef std::vector<ObjectData*>::const_iterator iterator;
typedef std::vector<CollidingPair>::const_iterator pair_iterator;
typedef std::vector<Collision>::const_iterator collision_iterator;

static const int calc_koef = 5;

PhysicsWorld::~PhysicsWorld()
{
    clear();
}

void PhysicsWorld::addObject(PhysicsObject *object)
{
    bool found = false;
    for (iterator i = objects.begin(); i != objects.end(); i++)
    {
        found |= ((*i)->object == object);
    }
    if (!found)
    {
        objects.push_back(new ObjectData(object));
    }
}

void PhysicsWorld::removeObject(PhysicsObject *object)
{
    iterator r = objects.end();
    for (iterator i = objects.begin(); i != objects.end(); i++)
    {
       if ((*i)->object == object)
       {
           r = i;
       }
    }
    if (r != objects.end())
    {
        delete (*r);
        objects.erase(r);
    }
}

std::vector<ObjectData*> PhysicsWorld::getObjectDatas()
{
    return objects;
}

void PhysicsWorld::clear()
{
    for (iterator i = objects.begin(); i != objects.end(); i++) {
        delete (*i);
    }
    objects.clear();
}

void PhysicsWorld::broadCollisionSearch(double dt)
{
    potentially_colliding.clear();
    for (iterator i = objects.begin(); i != objects.end(); i++) {
        for (iterator j = objects.begin(); j != objects.end(); j++) {
            if (i < j) {
                potentially_colliding.push_back(CollidingPair((*i), (*j)));
            }
        }
    }
}

void PhysicsWorld::narrowCollisionSearch(double dt)
{
    colliding_pairs.clear();
    for (pair_iterator i = potentially_colliding.begin(); i != potentially_colliding.end(); i++)
    {
        if ((*i).o1->object->collidesWith((*i).o2->object, dt))
        {
            //std::string string = (*i).o1->object->getType() + " collides with " + (*i).o2->object->getType();
            //Console::print(string.data());
            colliding_pairs.push_back(CollidingPair((*i).o1, (*i).o2));
        }
    }
}

void PhysicsWorld::collisionSolving(double dt)
{
    for (iterator i = objects.begin(); i != objects.end(); i++)
    {
        (*i)->collisions.clear();
    }
    for (pair_iterator i = colliding_pairs.begin(); i != colliding_pairs.end(); i++)
    {
        Collision c12 = i->o1->object->solveCollisionWith(i->o2->object, dt);
        Collision c21 = c12;
        c21.impulse_change.mul(-1);
        c21.relative_speed.mul(-1);
        c21.source = i->o1->object;
        i->o1->collisions.push_back(c12);
        i->o2->collisions.push_back(c21);
    }
}

void PhysicsWorld::changingStates(double dt)
{
    for (iterator i = objects.begin(); i != objects.end(); i++)
    {
        std::vector<PhysicsObject*> result = (*i)->object->calculateInnerState(dt);
        for (std::vector<PhysicsObject*>::iterator j = result.begin(); j != result.end(); j++)
        {
            addObject(*j);
        }
        for (collision_iterator it = (*i)->collisions.begin(); it != (*i)->collisions.end(); it++)
        {
            (*i)->object->applyCollision(*it, dt);
        }
    }
}

void PhysicsWorld::integrating(double dt)
{
    for (iterator i = objects.begin(); i != objects.end(); i++)
    {
        (*i)->object->tick(dt);
    }
}

void PhysicsWorld::tick(double dt)
{
    double ddt = dt / calc_koef;
    for (int i = 0; i < calc_koef; i++)
    {
        broadCollisionSearch(ddt);
        narrowCollisionSearch(ddt);
        collisionSolving(ddt);
        changingStates(ddt);
        integrating(ddt);
    }
}

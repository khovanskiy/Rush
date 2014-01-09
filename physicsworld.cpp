#include "physicsworld.h"
#include <algorithm>
#include "console.h"

typedef std::vector<ObjectData*>::const_iterator iterator;
typedef std::vector<CollidingPair>::const_iterator pair_iterator;
typedef std::vector<Collision>::const_iterator collision_iterator;
typedef std::pair<ObjectData*, AABB> pair;

static const int calc_koef = 1;
static const int sweep_and_prune_iterations = 2;
static const double INFINITY = 1e6;
static const double eps = 1e-3;

PhysicsWorld::~PhysicsWorld()
{
    clear();
}

void PhysicsWorld::addObject(PhysicsObject *object)
{
    objects.push_back(new ObjectData(object));
    new_objects.push_back(object);
}

void PhysicsWorld::removeObject(PhysicsObject *object)
{
    object->invalidate();
}

std::vector<ObjectData*> PhysicsWorld::getObjectDatas()
{
    return objects;
}

std::vector<PhysicsObject*> PhysicsWorld::popNewObjects()
{
    std::vector<PhysicsObject*> result(this->new_objects);
    this->new_objects.clear();
    return result;
}

void PhysicsWorld::clear()
{
    this->closed = true;
    for (iterator i = objects.begin(); i != objects.end(); i++) {
        (*i)->object->invalidate();
        to_delete.push_back((*i)->object);
    }
    for (auto i = to_delete.begin(); i != to_delete.end(); i++)
    {
        delete *i;
    }
    objects.clear();
    new_objects.clear();
    to_delete.clear();
    this->closed = false;
}

bool PhysicsWorld::isClosed()
{
    return closed;
}

void PhysicsWorld::broadCollisionSearch()
{
    potentially_colliding.clear();
    std::vector<pair> x_vector;
    for (iterator i = objects.begin(); i != objects.end(); i++)
    {
        x_vector.push_back(pair((*i), (*i)->object->getAABB()));
    }
    xCollisionSearch(x_vector, 1);
}

void PhysicsWorld::xCollisionSearch(std::vector<pair> x_colliding, int iteration)
{
    if (iteration <= sweep_and_prune_iterations)
    {
        std::sort(x_colliding.begin(), x_colliding.end(),
                  [](const pair & a, const pair & b)
        {
           return a.second.left < b.second.left;
        });
        std::vector<pair> y_vector;
        double max_right = -INFINITY;
        for (auto i = x_colliding.begin(); i != x_colliding.end(); i++)
        {
            if ((y_vector.size() == 0) || (i->second.left < max_right - eps))
            {
                y_vector.push_back(*i);
                if (i->second.right > max_right) max_right = i->second.right;
            }
            else
            {
                yCollisionSearch(y_vector, iteration);
                y_vector.clear();
                y_vector.push_back(*i);
                if (i->second.right > max_right) max_right = i->second.right;
            }
        }
        yCollisionSearch(y_vector, iteration);
    }
    else
    {
        addColliding(x_colliding);
    }
}

void PhysicsWorld::yCollisionSearch(std::vector<pair> y_colliding, int iteration)
{
    std::sort(y_colliding.begin(), y_colliding.end(),
              [](const pair & a, const pair & b)
    {
       return a.second.bottom < b.second.bottom;
    });
    std::vector<pair> x_vector;
    double max_top = -INFINITY;
    for (auto i = y_colliding.begin(); i != y_colliding.end(); i++)
    {
        if ((x_vector.size() == 0) || (i->second.bottom < max_top - eps))
        {
            x_vector.push_back(*i);
            if (i->second.top > max_top) max_top = i->second.top;
        }
        else
        {
            xCollisionSearch(x_vector, iteration + 1);
            x_vector.clear();
            x_vector.push_back(*i);
            if (i->second.top > max_top) max_top = i->second.top;
        }
    }
    xCollisionSearch(x_vector, iteration + 1);
}

void PhysicsWorld::addColliding(std::vector<pair> colliding)
{
    for (auto ii = colliding.begin(); ii != colliding.end(); ii++)
    {
        for (auto jj = ii; jj != colliding.end();)
        {
            jj++;
            if (jj != colliding.end())
            {
                if (ii->second.cross(jj->second))
                    potentially_colliding.push_back(CollidingPair(ii->first, jj->first));
            }
        }
    }
}

void PhysicsWorld::narrowCollisionSearch()
{
    colliding_pairs.clear();
    for (pair_iterator i = potentially_colliding.begin(); i != potentially_colliding.end(); i++)
    {
        if ((*i).o1->object->collidesWith((*i).o2->object))
        {
            colliding_pairs.push_back(CollidingPair((*i).o1, (*i).o2));
        }
    }
}

void PhysicsWorld::collisionSolving()
{
    for (iterator i = objects.begin(); i != objects.end(); i++)
    {
        (*i)->collisions.clear();
    }
    for (pair_iterator i = colliding_pairs.begin(); i != colliding_pairs.end(); i++)
    {
        Collision c12 = i->o1->object->solveCollisionWith(i->o2->object);
        Collision c21 = c12;
        c21.impulse_change.mul(-1);
        c21.relative_speed.mul(-1);
        c21.source = i->o1->object;
        i->o1->collisions.push_back(c12);
        i->o2->collisions.push_back(c21);
    }
}

std::vector<PhysicsObject*> PhysicsWorld::changingStates(double dt)
{
    std::vector<PhysicsObject*> n_objects;
    std::vector<ObjectData*> data;
    for (iterator i = objects.begin(); i != objects.end(); i++)
    {
        std::vector<PhysicsObject*> result = (*i)->object->calculateInnerState(dt);
        for (auto ii = result.begin(); ii != result.end(); ii++)
        {
            n_objects.push_back(*ii);
        }
        if ((*i)->object->isValid())
        {
            (*i)->object->applyCollisions((*i)->collisions);
            data.push_back(*i);
        }
        else
        {
            to_delete.push_back((*i)->object);
        }
    }
    this->objects = data;
    return n_objects;
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
    deleteInvalidObjects();
    double ddt = dt / calc_koef;
    for (int i = 0; i < calc_koef; i++)
    {        
        std::vector<PhysicsObject*> n_objects = changingStates(ddt);
        addingObjects(n_objects);
        integrating(ddt);
        broadCollisionSearch();
        narrowCollisionSearch();
        collisionSolving();
    }
}

void PhysicsWorld::addingObjects(const std::vector<PhysicsObject *> &n_objects)
{
    for (auto i = n_objects.begin(); i != n_objects.end(); i++)
    {
        addObject(*i);
    }
}

void PhysicsWorld::deleteInvalidObjects()
{
    for (auto i = to_delete.begin(); i != to_delete.end(); i++)
    {
        delete *i;
    }
    to_delete.clear();
}

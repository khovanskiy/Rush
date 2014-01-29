#include "physicsworld.h"
#include <algorithm>
//#include <QElapsedTimer>
#include "console.h"
#include "math.h"

typedef std::pair<ObjectData*, AABB> pair;

static const int calc_koef = 1;
static const int max_collisions_per_pair = 5;
static const double INFINITY = 1e6;
static const double eps = 1e-3;

PhysicsWorld::PhysicsWorld()
{
    this->tree = 0;
}

void PhysicsWorld::removeObjectNode(ObjectNode *node)
{
    node->data->object->invalidate();
    if (tree != 0 && node->position != 0) tree->remove(node);
    to_delete.push_back(node);
}

void PhysicsWorld::removeProjectile(ObjectData *projectile)
{
    projectile->object->invalidate();
    projectiles_to_delete.push_back(projectile);
}

PhysicsWorld::~PhysicsWorld()
{
    for (auto i = nodes.begin(); i != nodes.end(); i++) {
        removeObjectNode(*i);
    }
    for (auto i = projectiles.begin(); i != projectiles.end(); i++) {
        removeProjectile(*i);
    }
    deleteInvalidObjects();
    delete tree;
}

void PhysicsWorld::addObject(PhysicsObject *object)
{
    ObjectData* object_data = new ObjectData(object);
    new_objects.push_back(object_data);
    if (object->isProjectile())
    {
        projectiles.push_back(object_data);
    }
    else
    {
        ObjectNode* node = new ObjectNode(object_data, object->getAABB());
        nodes.push_back(node);
    }
}

std::vector<ObjectData*> PhysicsWorld::popNewObjects()
{
    std::vector<ObjectData*> result(this->new_objects);
    this->new_objects.clear();
    return result;
}

void PhysicsWorld::clear()
{
    int num = nodes.size();
    if (num > 0)
    {
        ObjectNode** ptr = &nodes.front();
        for (int i = 0; i < num; i++)
        {
            removeObjectNode(ptr[i]);
        }
        nodes.clear();
    }
    num = projectiles.size();
    if (num > 0)
    {
        ObjectData** ptr = &projectiles.front();
        for (int i = 0; i < num; i++)
        {
            removeProjectile(ptr[i]);
        }
        projectiles.clear();
    }
    delete tree;
    tree = 0;
    new_objects.clear();
}

void PhysicsWorld::broadCollisionSearch()
{
    potentially_colliding.clear();
    if (nodes.size() > 0)
    {
        double minx = +INFINITY, maxx = -INFINITY, miny = +INFINITY, maxy = -INFINITY;
        const int num = nodes.size();
        ObjectNode** ptr = &nodes.front();
        for (int i = 0; i < num; i++)
        {
            ptr[i]->bounds = ptr[i]->data->object->getAABB();
            if (ptr[i]->bounds.left < minx) minx = ptr[i]->bounds.left;
            if (ptr[i]->bounds.right > maxx) maxx = ptr[i]->bounds.right;
            if (ptr[i]->bounds.bottom < miny) miny = ptr[i]->bounds.bottom;
            if (ptr[i]->bounds.top > maxy) maxy = ptr[i]->bounds.top;
        }
        AABB boundary(minx, maxx, miny, maxy);
        if (tree == 0)
        {
            tree = new QuadTree(boundary, 0);
        }
        else
        {
            tree = tree->resize(boundary);
        }
        for (int i = 0; i < num; i++)
        {
            if (ptr[i]->position == 0)
            {
                tree->insert(ptr[i]);
            }
            else
            {
                tree->update(ptr[i]);
            }
        }
        std::vector<ObjectData*> response;
        for (int i = 0; i < num; i++)
        {
            tree->queryAABB(ptr[i]->bounds, response);
            const int num_r = response.size();
            if (num_r > 1)
            {
                ObjectData** ptr_r = &response.front();
                for (int j = 0; j < num_r; j++)
                {
                    if (ptr[i]->data != ptr_r[j])
                    {
                        potentially_colliding.push_back(std::pair<ObjectData*, ObjectData*>(ptr[i]->data, ptr_r[j]));
                    }
                }
            }
            response.clear();
        }
    }
    int num = projectiles.size();
    if (tree != 0 && num > 0)
    {
        ObjectData** ptr = &projectiles.front();
        std::vector<ObjectData*> response;
        for (int i = 0; i < num; i++)
        {
            tree->queryAABB(ptr[i]->object->getAABB(), response);
            int num_r = response.size();
            if (num_r > 0)
            {
                ObjectData** ptr_r = &response.front();
                for (int j = 0; j < num_r; j++)
                {
                    potentially_colliding.push_back(std::pair<ObjectData*, ObjectData*>(ptr[i], ptr_r[j]));
                }
            }
            response.clear();
        }
    }
}


void PhysicsWorld::narrowCollisionSearch()
{
    const int num = potentially_colliding.size();
    if (num > 0)
    {
        std::pair<ObjectData*, ObjectData*>* ptr = &potentially_colliding.front();
        for (int i = 0; i < num; i++)
        {
            CrossingResult2D result = ptr[i].first->object->collidesWith(ptr[i].second->object);
            if (result.crossing)
            {
                colliding_pairs.push(CollidingPair(ptr[i].first, ptr[i].second, result.center, max_collisions_per_pair));
            }
        }
    }

}

void PhysicsWorld::collisionSolving(double dt)
{
    while (!colliding_pairs.empty())
    {
        CollidingPair colliding_pair = colliding_pairs.front();
        colliding_pairs.pop();
        if ((colliding_pair.remained_collisions == max_collisions_per_pair)
            ||(colliding_pair.o1->object->isValid() && colliding_pair.o2->object->isValid()
                && colliding_pair.o1->object->collidesWith(colliding_pair.o2->object).crossing))
        {
            Collision collision = colliding_pair.o1->object->solveCollisionWith(colliding_pair.o2->object, colliding_pair.center);
            colliding_pair.o1->collisions.push_back(collision);
            colliding_pair.o1->object->applyCollision(collision, dt);
            collision.impulse_change.mul(-1);
            collision.relative_speed.mul(-1);
            collision.source = colliding_pair.o1->object;
            colliding_pair.o2->collisions.push_back(collision);
            colliding_pair.o2->object->applyCollision(collision, dt);
            if (colliding_pair.remained_collisions > 0)
            {
                colliding_pair.remained_collisions--;
                colliding_pairs.push(colliding_pair);
            }
        }
    }
}

void PhysicsWorld::changingStates(double dt, std::vector<PhysicsObject*>& n_objects)
{
    int num = nodes.size();
    if (num > 0)
    {
        std::vector<ObjectNode*> remaining;
        ObjectNode** ptr = &nodes.front();
        for (int i = 0; i < num; i++)
        {
            std::vector<PhysicsObject*>* result = ptr[i]->data->object->calculateInnerState(dt);
            if (result != 0)
            {
                for (auto ii = result->begin(); ii != result->end(); ii++)
                {
                    n_objects.push_back(*ii);
                }
                delete result;
            }
            if (ptr[i]->data->object->isValid())
            {                
                remaining.push_back(ptr[i]);
            }
            else
            {
                removeObjectNode(ptr[i]);
            }
        }
        this->nodes = remaining;
    }
    num = projectiles.size();
    if (num > 0)
    {
        std::vector<ObjectData*> remaining;
        ObjectData** ptr = &projectiles.front();
        for (int i = 0; i < num; i++)
        {
            std::vector<PhysicsObject*>* result = ptr[i]->object->calculateInnerState(dt);
            if (result != 0)
            {
                for (auto ii = result->begin(); ii != result->end(); ii++)
                {
                    n_objects.push_back(*ii);
                }
                delete result;
            }
            if (ptr[i]->object->isValid())
            {
                remaining.push_back(ptr[i]);
            }
            else
            {
                removeProjectile(ptr[i]);
            }
        }
        this->projectiles = remaining;
    }
}

void PhysicsWorld::integrating(double dt)
{
    int num = nodes.size();
    if (num > 0)
    {
        ObjectNode** ptr = &nodes.front();
        for (int i = 0; i < num; i++)
        {
            ptr[i]->data->object->tick(dt);
        }
    }
    num = projectiles.size();
    if (num > 0)
    {
        ObjectData** ptr = &projectiles.front();
        for (int i = 0; i < num; i++)
        {
            ptr[i]->object->tick(dt);
        }
    }
}

void PhysicsWorld::collisionSearch(double dt)
{
    broadCollisionSearch();
    narrowCollisionSearch();
    collisionSolving(dt);
}

void PhysicsWorld::tick(double dt)
{
    deleteInvalidObjects();
    int num = nodes.size();
    if (num > 0)
    {
        ObjectNode** ptr = &nodes.front();
        for (int i = 0; i < num; i++)
        {
            ptr[i]->data->collisions.clear();
        }
    }
    num = projectiles.size();
    if (num > 0)
    {
        ObjectData** ptr = &projectiles.front();
        for (int i = 0; i < num; i++)
        {
            ptr[i]->collisions.clear();
        }
    }
    double ddt = dt / calc_koef;
    for (int i = 0; i < calc_koef; i++)
    {
        integrating(ddt);
        std::vector<PhysicsObject*> n_objects;
        changingStates(ddt, n_objects);
        addingObjects(n_objects);
        collisionSearch(ddt);
    }
}

void PhysicsWorld::addingObjects(std::vector<PhysicsObject *> &n_objects)
{
    int num = n_objects.size();
    if (num > 0)
    {
        PhysicsObject** ptr = &n_objects.front();
        for (int i = 0; i < num; i++)
        {
            addObject(ptr[i]);
        }
    }

}

void PhysicsWorld::deleteInvalidObjects()
{
    int num = to_delete.size();
    if (num > 0)
    {
        ObjectNode** ptr = &to_delete.front();
        for (int i = 0; i < num; i++)
        {
            delete ptr[i];
        }
        to_delete.clear();
    }
    num = projectiles_to_delete.size();
    if (num > 0)
    {
        ObjectData** ptr = &projectiles_to_delete.front();
        for (int i = 0; i < num; i++)
        {
            delete ptr[i];
        }
        projectiles_to_delete.clear();
    }
}

#include "physicsworld.h"

#include <algorithm>
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

PhysicsWorld::~PhysicsWorld()
{
    for (int i = 0; i < nodes.size(); ++i)
    {
        delete nodes[i];
    }
    for (int i = 0; i < projectiles.size(); ++i)
    {
        delete projectiles[i];
    }
    delete tree;
}

void PhysicsWorld::add(PhysicsObject *object)
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

void PhysicsWorld::broadCollisionSearch()
{
    potentially_colliding.clear();
    if (nodes.size() > 0)
    {
        double minx = +INFINITY, maxx = -INFINITY, miny = +INFINITY, maxy = -INFINITY;
        const int num = (int)nodes.size();
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
            const int num_r = (int)response.size();
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
    int num = (int)projectiles.size();
    if (tree != 0 && num > 0)
    {
        ObjectData** ptr = &projectiles.front();
        std::vector<ObjectData*> response;
        for (int i = 0; i < num; i++)
        {
            tree->queryAABB(ptr[i]->object->getAABB(), response);
            int num_r = (int)response.size();
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
    const int num = (int)potentially_colliding.size();
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

void PhysicsWorld::changingStates(double dt)
{
    for (int i = 0; i < nodes.size(); ++i)
    {
        if (nodes[i]->data->object->isValid())
        {
            nodes[i]->data->object->calculateInnerState(dt);
        }
        else
        {
            ObjectNode* node = nodes[i];
            if (tree != 0)
            {
                tree->remove(node);
            }
            delete node;

            nodes[i] = nodes[nodes.size() - 1];
            nodes.pop_back();
            --i;
        }
    }
    for (int i = 0; i < projectiles.size(); ++i)
    {
        if (projectiles[i]->object->isValid())
        {
            projectiles[i]->object->calculateInnerState(dt);
        }
        else
        {
            delete projectiles[i];
            projectiles[i] = projectiles[projectiles.size() - 1];
            projectiles.pop_back();
            --i;
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
    for (std::vector<ObjectNode*>::iterator i = nodes.begin(); i != nodes.end(); ++i)
    {
        (*i)->data->collisions.clear();
    }
    for (std::vector<ObjectData*>::iterator i = projectiles.begin(); i != projectiles.end(); ++i)
    {
        (*i)->collisions.clear();
    }

    double ddt = dt / calc_koef;
    for (int i = 0; i < calc_koef; i++)
    {
        changingStates(ddt);
        collisionSearch(ddt);
    }
}

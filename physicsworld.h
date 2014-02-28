#ifndef PHYSICSWORLD_H
#define PHYSICSWORLD_H
#include <vector>
#include <queue>
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
    int remained_collisions;

    CollidingPair(ObjectData* o1, ObjectData* o2, Point2D center, int remained_collisions)
        : center(center), remained_collisions(remained_collisions)
    {
        this->o1 = o1;
        this->o2 = o2;
    }
};

class QuadTree;

struct ObjectNode
{
    QuadTree * position;
    ObjectData * data;
    AABB bounds;

    ObjectNode(ObjectData* data, AABB bounds)
        : data(data), bounds(bounds)
    {
        position = 0;
    }

    ~ObjectNode()
    {
        delete data;
    }
};

class QuadTree
{
    static const int minimal_filling = 10;
    AABB boundary;

    std::vector<ObjectNode*> obj_pairs;

    QuadTree* parent;
    QuadTree* northWest;
    QuadTree* northEast;
    QuadTree* southWest;
    QuadTree* southEast;

    void subdivide()
    {
        double midX = (boundary.left + boundary.right) / 2;
        double midY = (boundary.bottom + boundary.top) / 2;
        northWest = new QuadTree(AABB(boundary.left, midX, midY, boundary.top), this);
        northEast = new QuadTree(AABB(midX, boundary.right, midY, boundary.top), this);
        southWest = new QuadTree(AABB(boundary.left, midX, boundary.bottom, midY), this);
        southEast = new QuadTree(AABB(midX, boundary.right, boundary.bottom, midY), this);
    }

    void innerRemove(ObjectNode* node)
    {
        auto position = std::find(obj_pairs.begin(), obj_pairs.end(), node);
        if (position != obj_pairs.end())
        {
            obj_pairs.erase(position);
        }
    }

    void innerUpdate(ObjectNode* node)
    {
        if (!this->boundary.contains(node->bounds))
        {
            innerRemove(node);
            this->siftUp(node);
        }
    }

    void siftUp(ObjectNode* node)
    {
        if (this->boundary.contains(node->bounds))
        {
            obj_pairs.push_back(node);
            node->position = this;
        }
        else if (this->parent != 0)
        {
            this->parent->siftUp(node);
        }
    }


public:
    QuadTree(AABB boundary, QuadTree* parent)
        : boundary(boundary), parent(parent)
    {
        northWest = 0;
        northEast = 0;
        southWest = 0;
        southEast = 0;
    }

    ~QuadTree()
    {
        if (northWest != 0)
        {
            delete northWest;
            delete northEast;
            delete southWest;
            delete southEast;
        }
    }

    bool insert(ObjectNode* node)
    {
        if (boundary.contains(node->bounds))
        {
            if (northWest == 0) subdivide();
            if (obj_pairs.size() < minimal_filling)
            {
                obj_pairs.push_back(node);
                node->position = this;
                return true;
            }
            else
            {
                bool result = northWest->insert(node)
                        || northEast->insert(node)
                        || southEast->insert(node)
                        || southWest->insert(node);
                if (!result)
                {
                    obj_pairs.push_back(node);
                    node->position = this;
                }
                return true;
            }
        }
        else return false;
    }

    void remove(ObjectNode* node)
    {
        node->position->innerRemove(node);
    }

    void update(ObjectNode* node)
    {
        node->position->innerUpdate(node);
    }

    void queryAABB(AABB const & query, std::vector<ObjectData*>& response)
    {
        if (boundary.cross(query))
        {
            const int num = (int)obj_pairs.size();
            if (num > 0)
            {
                ObjectNode** ptr = &obj_pairs.front();
                for (int i = 0; i < num; i++)
                {
                    if (query.cross(ptr[i]->bounds))
                    {
                        response.push_back(ptr[i]->data);
                    }
                }
            }
            if (northWest != 0)
            {
                northWest->queryAABB(query, response);
                northEast->queryAABB(query, response);
                southWest->queryAABB(query, response);
                southEast->queryAABB(query, response);
            }
        }
    }

    int getSize()
    {
        int size = (int)obj_pairs.size();
        if (northWest != 0)
        {
            size += northWest->getSize();
            size += northEast->getSize();
            size += southEast->getSize();
            size += southWest->getSize();
        }
        return size;
    }

    QuadTree* resize(AABB const & boundary)
    {
        if (!this->boundary.contains(boundary))
        {
            QuadTree* result = this;
            while (result->boundary.left > boundary.left || result->boundary.bottom > boundary.bottom)
            {
                QuadTree* r = new QuadTree(
                            AABB(2 * result->boundary.left - result->boundary.right,
                                 result->boundary.right,
                                 2 * result->boundary.bottom - result->boundary.top,
                                 result->boundary.top), 0);
                r->subdivide();
                delete r->northEast;
                r->northEast = result;
                result->parent = r;
                result = r;
            }
            while (result->boundary.right < boundary.right || result->boundary.top < boundary.top)
            {
                QuadTree* r = new QuadTree(
                            AABB(result->boundary.left,
                                 2 * result->boundary.right - result->boundary.left,
                                 result->boundary.bottom,
                                 2 * result->boundary.top - result->boundary.bottom), 0);
                r->subdivide();
                delete r->southWest;
                r->southWest = result;
                result->parent = r;
                result = r;
            }
            return result;
        }
        else
        {
            return this;
        }
    }
};

class PhysicsWorld
{
    QuadTree* tree;

    std::vector<ObjectNode*> nodes;
    std::vector<ObjectData*> projectiles;
    std::vector<ObjectNode*> to_delete;
    std::vector<ObjectData*> projectiles_to_delete;


    std::vector<ObjectData*> new_objects;
    std::queue<CollidingPair> colliding_pairs;
    std::vector<std::pair<ObjectData*, ObjectData*>> potentially_colliding;

    PhysicsWorld();
    PhysicsWorld(PhysicsWorld const &);
    void operator=(PhysicsWorld const&);
    ~PhysicsWorld();

    void broadCollisionSearch();
    void narrowCollisionSearch();
    void collisionSolving(double dt);
    void collisionSearch(double dt);
    void changingStates(double dt, std::vector<PhysicsObject*> & n_objects);
    void integrating(double dt);
    void addingObjects(std::vector<PhysicsObject*> & n_objects);
    void removeObjectNode(ObjectNode* node);
    void removeProjectile(ObjectData* projectile);
    void deleteInvalidObjects();    

public:
    static PhysicsWorld& gi()
    {
        static PhysicsWorld instance;
        return instance;
    }

    void addObject(PhysicsObject* object);
    std::vector<ObjectData*> popNewObjects();
    void clear();
    void tick(double dt);
};

#endif // PHYSICSWORLD_H

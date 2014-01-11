#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
<<<<<<< HEAD

#include <map>

class GameObject
{
public:
    GameObject(__int64 id);
    virtual ~GameObject();
    static GameObject* findById(__int64 id);
    __int64 getId();
    void setId(__int64);
private:
    void insert(__int64, const GameObject*);
    void erase(__int64);
    __int64 my_id;
    static std::map<__int64, GameObject*> table;
=======
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
>>>>>>> origin/physicsDebug
};

#endif // GAMEOBJECT_H

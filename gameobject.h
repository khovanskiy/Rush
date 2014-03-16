#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <map>

class GameObject
{
public:
    GameObject(__int64 id);
    virtual ~GameObject();

    void add(GameObject* go);
    void update(double dt);

    static GameObject* findById(__int64 id);
    __int64 getId();
    void setId(__int64);
private:

    static std::map<__int64, GameObject*> table;
    void insert(__int64, const GameObject*);
    void erase(__int64);
    __int64 my_id;


};

#endif // GAMEOBJECT_H

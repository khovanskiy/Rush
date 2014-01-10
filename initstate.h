#ifndef NULLSTATE_H
#define NULLSTATE_H

#include "state.h"
#include "bitmap.h"
#include <memory>
#include "physicsworld.h"
#include "statecontext.h"
#include "gameobject.h"

class InitState : virtual public State
{
public:
    InitState();
    virtual ~InitState();
    void init();
    void focus();
    void tick(double dt);
    void defocus();
    void release();
    void Invoke(const Event &event);

private:
    double time;
    void addPhysicsObject(PhysicsObject* object);
    void addGameObject(GameObject* game_object);
    void addAllBitmaps(GameObject* game_object);
    void removeAllBitmaps(GameObject* game_object);
    void getNewPhysicsObjects();
    void renewGameObjects();
    std::vector<GameObject*> game_objects;
    Vehicle* dodge;
};

#endif // NULLSTATE_H

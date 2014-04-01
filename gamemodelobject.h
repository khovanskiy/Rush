#ifndef GAMEMODELOBJECT_H
#define GAMEMODELOBJECT_H

#include <map>
#include <vector>

#include "eventdispatcher.h"
#include "gameobjectevent.h"

enum GameObjectType
{
    VEHICLE, TURRET, BULLET, UNKNOWN
};

class GameModelObject : public EventDispatcher, public EventHandler
{
public:
    GameModelObject(__int64 id);
    GameModelObject();
    virtual ~GameModelObject();

    void add(GameModelObject* go);
    const std::vector<GameModelObject*>& getInners() const;

    virtual void tick(double dt);
    bool isValid();
    void invalidate();
    virtual GameObjectType getFamilyId();
protected:
    std::vector<GameModelObject*> inners;
private:
    bool valid;
};

#endif // GAMEMODELOBJECT_H

#ifndef GAMEMODELOBJECT_H
#define GAMEMODELOBJECT_H

#include <map>
#include <vector>

#include "common/eventdispatcher.h"
#include "common/GameObjectType.h"

class GameModelObject : public EventDispatcher, public EventHandler
{
public:
    GameModelObject(int my_id);
    virtual ~GameModelObject();

    void add(GameModelObject* go);
    static GameModelObject* findById(int id);
    const std::vector<GameModelObject*>& getInners() const;

    virtual void tick(double dt);
    bool isValid();
    void invalidate();
    virtual GameObjectType getFamilyId();

    int my_id;
    int type_object;
protected:
    std::vector<GameModelObject*> inners;
private:
    static std::map<int, GameModelObject*> registry;
    bool valid;
};

#endif // GAMEMODELOBJECT_H

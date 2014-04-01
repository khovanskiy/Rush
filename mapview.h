#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <vector>
#include "displayobject.h"
#include "gameworld.h"
#include "vehicleview.h"
#include "bulletview.h"
#include "stage.h"
#include "sprite.h"

class MapView : public EventHandler
{
public:
    MapView(GameWorld*);
    virtual ~MapView();
    void Invoke(const Event &);
    void update();
protected:
    void createObject(GameModelObject* go);
private:
    std::vector<GameViewObject*> unused;
    std::vector<GameViewObject*> list;
    GameWorld* world;
};


#endif // MAPVIEW_H

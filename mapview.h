#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <vector>
#include "displayobject.h"
#include "gameworld.h"
#include "vehicleview.h"
#include "bulletview.h"
#include "stage.h"

class MapView : public EventHandler
{
public:
    MapView(GameWorld*);
    void Invoke(const Event &);
protected:
    void createObject(GameModelObject* go);
private:
    std::vector<DisplayObject*> list;
    GameWorld* world;
};


#endif // MAPVIEW_H

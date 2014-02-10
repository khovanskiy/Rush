#ifndef MAPVIEW_H
#define MAPVIEW_H
#include "gameviewobjectfactory.h"
#include "gameworld.h"
#include "stage.h"

class MapView
{
    std::vector<GameViewObject*> game_view_objects;
    std::vector<GameViewObject*> to_delete;

    MapView()
    {
    }
    MapView(MapView const &);
    void operator=(MapView const&);
    ~MapView();

    void deleteInvalidObjects();
    void addGameViewObject(GameViewObject* game_view_object);
    void removeFromScene(GameViewObject* game_view_object);
    void addToScene(GameViewObject* game_view_object);


public:
    static MapView& gi()
    {
        static MapView instance;
        return instance;
    }
    void tick(double dt);
    void updateView(double scale, Vector2D d_r, double d_angle, Vector2D center);
    void clear();
};

#endif // MAPVIEW_H

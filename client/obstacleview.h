#ifndef OBSTACLEVIEW_H
#define OBSTACLEVIEW_H

#include "../common/obstacle.h"
#include "gameviewobject.h"
#include "bitmap.h"

class ObstacleView : public GameViewObject, EventHandler
{
public:
    ObstacleView(Obstacle* obstacle);
    virtual ~ObstacleView();
    void Invoke(const Event &);
    void render(QPainter *render2d, const Matrix &base, bool new_frame, float interpolation);
private:
    Bitmap* body;
    Obstacle* obstacle;
};

#endif // OBSTACLEVIEW_H

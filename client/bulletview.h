#ifndef BULLETVIEW_H
#define BULLETVIEW_H

#include "../common/bullet.h"
#include "gameviewobject.h"
#include "bitmap.h"

class BulletView : public GameViewObject, public EventHandler
{
public:
    BulletView(Bullet* bullet);
    virtual ~BulletView();
    void render(QPainter *render2d, const Matrix &base, bool new_frame, float interpolation);
    void Invoke(const Event &);
protected:
    Bitmap* body;
    Bullet* bullet;
};

#endif // BULLETVIEW_H

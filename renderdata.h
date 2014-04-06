#ifndef RENDERDATA_H
#define RENDERDATA_H

#include <QPainter>

class RenderData
{
public:
    RenderData();
    QPainter* render2d;
    float interpolation;
};

#endif // RENDERDATA_H

#ifndef GRAPHICCORE_H
#define GRAPHICCORE_H

#include <QGLWidget>
#include <QPainter>
#include <QImage>
#include <QPen>
#include <QTimer>

#include "displayobjectcontainer.h"
#include "eventdispatcher.h"

class EventDispatcher;

class GraphicCore : public QGLWidget, public EventDispatcher
{
public:
    GraphicCore();
    ~GraphicCore();
    static GraphicCore* gi();
    void render(float interpolation);
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
    void resizeEvent(QResizeEvent *);
private:
    //void render(DisplayObjectContainer* child);
    static GraphicCore* instance;
    QPainter* render2d;
    QPen* pen;
};

#endif // GRAPHICCORE_H

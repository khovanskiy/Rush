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
    void render(bool new_frame, float interpolation);
protected:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
    void resizeEvent(QResizeEvent *);
private:
    float current_interpolation;
    bool new_frame;
    float prev_interpolation;
    //void render(DisplayObjectContainer* child);
    static GraphicCore* instance;
    QPainter* render2d;
    QPen* pen;
};

#endif // GRAPHICCORE_H

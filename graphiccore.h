#ifndef GRAPHICCORE_H
#define GRAPHICCORE_H

#include <QGLWidget>
#include <QPainter>
#include <QImage>
#include <QPen>

#include "displayobjectcontainer.h"
#include "eventdispatcher.h"

class GraphicCore : public QGLWidget, public EventDispatcher
{
public:
    static GraphicCore* getInstance();
    void render();
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent *);
    void resizeEvent(QResizeEvent *);
private:
    //void render(DisplayObjectContainer* child);
    static GraphicCore* instance;
    QPainter* render2d;
    QPen* pen;
    GraphicCore();
    ~GraphicCore();
};

#endif // GRAPHICCORE_H

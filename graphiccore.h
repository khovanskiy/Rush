#ifndef GRAPHICCORE_H
#define GRAPHICCORE_H

#include "eventdispatcher.h"

#include <QtOpenGL>
#include <QGLWidget>
#include <QTimer>
#include <QElapsedTimer>
#include "statecontext.h"
#include <QMouseEvent>
#include "renderdata.h"

class GraphicCore : public QGLWidget, public EventDispatcher
{
    Q_OBJECT
public:
    GraphicCore();
    ~GraphicCore();
    static GraphicCore& gi();
    void render(bool new_tick, float interpolation);
public slots:
    void onGameCycle();
protected:
    void paintEvent(QPaintEvent*);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
    void resizeEvent(QResizeEvent *);
private:
    QPainter render2d;
    StateContext state_context;
    QTimer loop;
    QElapsedTimer counter;
    RenderData render_data;

    float current_interpolation;
    int TICKS_PER_SECOND;
    int SKIP_TICKS;
    int MAX_FRAMESKIP;
    long next_game_tick;
    int loops;
    float interpolation;
    bool new_tick, old_state;
};

#endif // GRAPHICCORE_H

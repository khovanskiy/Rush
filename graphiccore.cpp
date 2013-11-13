#include "graphiccore.h"

#include <QPainter>
#include <QImage>
#include <QMatrix>
#include <QMouseEvent>
#include <QKeyEvent>

#include "console.h"
#include "bitmap.h"
#include "background.h"
#include "stage.h"
#include "interface.h"
#include "event.h"
#include "mouse.h"
#include "keyboard.h"
#include "mouseevent.h"
#include "keyboardevent.h"
#include "camera.h"

GraphicCore* GraphicCore::instance = 0;

GraphicCore::GraphicCore() : QGLWidget(QGLFormat(QGL::SampleBuffers), 0)
{
    render2d = new QPainter();
    pen = new QPen(QColor(255,255,255));
    setWindowTitle("Rush game");
    resize(800, 600);
    setAutoFillBackground(false);
    show();
}

GraphicCore::~GraphicCore()
{
    delete pen;
    delete render2d;
}

GraphicCore* GraphicCore::gi()
{
    if (instance == 0)
    {
        instance = new GraphicCore();
    }
    return instance;
}

void GraphicCore::paintEvent(QPaintEvent*)
{
    render2d->begin(this);
    render2d->setBackground(QBrush(QColor(0,0,0)));
    render2d->eraseRect(QRect(this->rect()));
    render2d->setRenderHint(QPainter::Antialiasing);
    Background::gi()->render(render2d);
    Stage::gi()->render(render2d);
    Interface::gi()->render(render2d);
    render2d->end();
}

void GraphicCore::resizeEvent(QResizeEvent *event)
{
    //Console::print("RESIZE "+QVariant(event->size().width()).toString() + " " + QVariant(event->size().height()).toString());
    Camera::gi()->resize(event->size().width(), event->size().height());
}

void GraphicCore::mousePressEvent(QMouseEvent* event)
{
    dispatchEvent(MouseEvent(this, MouseEvent::CLICK, event->x(), event->y()));
}

void GraphicCore::keyPressEvent(QKeyEvent* event)
{
    dispatchEvent(KeyboardEvent(this, KeyboardEvent::KEY_DOWN, event->key()));
}

void GraphicCore::keyReleaseEvent(QKeyEvent* event)
{
    dispatchEvent(KeyboardEvent(this, KeyboardEvent::KEY_UP, event->key()));
}

void GraphicCore::render()
{
    repaint();
    dispatchEvent(Event(this, Event::ENTER_FRAME));
}

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

class Console;

GraphicCore::GraphicCore() : QGLWidget(QGLFormat(QGL::SampleBuffers), 0)
{
    render2d = new QPainter();
    pen = new QPen(QColor(255,255,255));
    setWindowTitle("OpenGL game");
    setFixedSize(Camera::getInstance()->width, Camera::getInstance()->height);
    setAutoFillBackground(false);
    show();
}

GraphicCore::~GraphicCore()
{
    delete pen;
    delete render2d;
}

GraphicCore* GraphicCore::getInstance()
{
    if (instance == 0)
    {
        Console::print("1. Init graphic core");
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
    Background::getInstance()->render(render2d);
    Stage::getInstance()->render(render2d);
    Interface::getInstance()->render(render2d);
    render2d->end();
}

void GraphicCore::resizeEvent(QResizeEvent *)
{
    //Console::print("resize");
}

void GraphicCore::mousePressEvent(QMouseEvent* event)
{
    dispatchEvent(MouseEvent(this, MouseEvent::CLICK, event->x(), event->y()));
}

void GraphicCore::keyPressEvent(QKeyEvent* event)
{
    dispatchEvent(KeyboardEvent(this, KeyboardEvent::KEY_UP, event->key()));
}

void GraphicCore::render()
{
    dispatchEvent(Event(this, Event::ENTER_FRAME));
    repaint();
}

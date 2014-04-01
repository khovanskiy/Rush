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
#include "matrix.h"

GraphicCore* GraphicCore::instance = 0;

GraphicCore::GraphicCore() : QGLWidget(QGLFormat(QGL::SampleBuffers), 0)
{
    render2d = new QPainter();
    //this->showFullScreen();
    pen = new QPen(QColor(255,255,255));
    setWindowTitle("Rush game");
    Camera::gi()->resize(1200, 800);
    resize(1200, 800);
    move(0,0);
    prev_interpolation = 0;
    setAutoFillBackground(false);
    setMouseTracking(true);
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
    render2d->setRenderHint(QPainter::SmoothPixmapTransform);
    Background::gi()->render(render2d, Matrix(), new_frame, current_interpolation);
    Stage::gi()->render(render2d, Camera::gi()->getTransform(), new_frame, current_interpolation);
    Interface::gi()->render(render2d, Matrix(), new_frame, current_interpolation);
    render2d->end();
}

void GraphicCore::resizeEvent(QResizeEvent *event)
{
    //Console::print("RESIZE "+QVariant(event->size().width()).toString() + " " + QVariant(event->size().height()).toString());
    Camera::gi()->resize(event->size().width(), event->size().height());
}

void GraphicCore::mouseMoveEvent(QMouseEvent *event)
{
    dispatchEvent(MouseEvent(this, MouseEvent::MOUSE_MOVE, event->x(), event->y()));
    event->accept();
}

void GraphicCore::mousePressEvent(QMouseEvent* event)
{
    dispatchEvent(MouseEvent(this, MouseEvent::MOUSE_DOWN, event->x(), event->y()));
    event->accept();
}

void GraphicCore::mouseReleaseEvent(QMouseEvent* event)
{
    dispatchEvent(MouseEvent(this, MouseEvent::MOUSE_UP, event->x(), event->y()));
    event->accept();
}

void GraphicCore::keyPressEvent(QKeyEvent* event)
{
    if (!event->isAutoRepeat())
    {
        dispatchEvent(KeyboardEvent(this, KeyboardEvent::KEY_DOWN, event->key()));
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void GraphicCore::keyReleaseEvent(QKeyEvent* event)
{
    if (!event->isAutoRepeat())
    {
        dispatchEvent(KeyboardEvent(this, KeyboardEvent::KEY_UP, event->key()));
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void GraphicCore::render(bool new_frame, float interpolation)
{
    this->new_frame = new_frame;
    this->current_interpolation = interpolation;
    repaint();
    //dispatchEvent(Event(this, Event::ENTER_FRAME));
}

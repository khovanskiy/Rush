#include <common/console.h>
#include "graphiccore.h"

#include "camera.h"
#include "mouse.h"
#include "keyboard.h"

GraphicCore::GraphicCore() : QGLWidget(QGLFormat(QGL::SampleBuffers), 0) {
    connect(&loop, SIGNAL(timeout()), this, SLOT(onGameCycle()));

    TICKS_PER_SECOND = 20;
    SKIP_TICKS = 1000 / TICKS_PER_SECOND;
    MAX_FRAMESKIP = 20;
    counter.start();
    new_tick = false;
    next_game_tick = counter.elapsed();
    loop.start(0);

    setWindowTitle("The Rush game 2016");
    this->resize(1200, 800);
    this->move(0, 0);
    this->setAutoFillBackground(false);
    this->setMouseTracking(true);

    render_data.render2d = &render2d;
}

GraphicCore::~GraphicCore() {

}

void GraphicCore::onGameCycle() {
    loops = 0;

    old_state = new_tick;

    /*if (counter.elapsed() > next_game_tick)
    {
        new_tick = true;
    }
    else
    {
        new_tick = false;
    }*/



    render_data.new_tick = old_state;

    while (counter.elapsed() > next_game_tick && loops < MAX_FRAMESKIP) {
        state_context.tick(1.0 / TICKS_PER_SECOND);
        render_data.new_tick = true;
        next_game_tick += SKIP_TICKS;
        loops++;
    }

    render_data.interpolation = (double) (counter.elapsed() + SKIP_TICKS - next_game_tick) / (double) (SKIP_TICKS);
    if (render_data.interpolation > 1 || render_data.interpolation < 0) {
        Console::print("bug               --                        --                          --                    --");
    }
    repaint();
}

void GraphicCore::paintEvent(QPaintEvent *) {
    render2d.begin(this);
    render2d.setBackground(QBrush(QColor(0, 0, 0)));
    render2d.eraseRect(QRect(this->rect()));
    render2d.setRenderHint(QPainter::Antialiasing);
    render2d.setRenderHint(QPainter::SmoothPixmapTransform);

    state_context.render(render_data);

    render2d.end();
}

void GraphicCore::resizeEvent(QResizeEvent *event) {
    //Console::print("RESIZE "+QVariant(event->size().width()).toString() + " " + QVariant(event->size().height()).toString());
    Camera::gi()->resize(event->size().width(), event->size().height());
}

void GraphicCore::mouseMoveEvent(QMouseEvent *event) {
    Mouse::gi()->Invoke(MouseEvent(this, MouseEvent::MOUSE_MOVE, event->x(), event->y()));
    event->accept();
}

void GraphicCore::mousePressEvent(QMouseEvent *event) {
    Mouse::gi()->Invoke(MouseEvent(this, MouseEvent::MOUSE_DOWN, event->x(), event->y()));
    event->accept();
}

void GraphicCore::mouseReleaseEvent(QMouseEvent *event) {
    Mouse::gi()->Invoke(MouseEvent(this, MouseEvent::MOUSE_UP, event->x(), event->y()));
    event->accept();
}

void GraphicCore::keyPressEvent(QKeyEvent *event) {
    if (!event->isAutoRepeat()) {
        Keyboard::gi()->Invoke(KeyboardEvent(this, KeyboardEvent::KEY_DOWN, event->key()));
        event->accept();
    }
    else {
        event->ignore();
    }
}

void GraphicCore::keyReleaseEvent(QKeyEvent *event) {
    if (!event->isAutoRepeat()) {
        Keyboard::gi()->Invoke(KeyboardEvent(this, KeyboardEvent::KEY_UP, event->key()));
        event->accept();
    }
    else {
        event->ignore();
    }
}

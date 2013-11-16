#include "initstate.h"
#include "console.h"
#include "state.h"
#include "stateevent.h"
#include "bitmap.h"
#include "mouseevent.h"
#include "stage.h"
#include "math.h"
#include "background.h"
#include "keyboard.h"
#include "keyboardevent.h"
#include "random"
#include "QCoreApplication"
#include "vehiclefactory.h"

static const double scale = 15;

InitState::InitState()
{
}

InitState::~InitState()
{
}

void InitState::init()
{
    v = VehicleFactory::createDodgeChallengerSRT8(Vector2D(20,20), asin(1), Vector2D(0, 0), 0);
    v->setTorquePercent(1);
    sb = new Bitmap();
    sb->load(QCoreApplication::applicationDirPath() + "\\DATA\\Textures\\Vehicles\\dodge.jpg");
    sb->setRSPointCenter();
    sb->setWidth(scale * v->getWidth());
    sb->setHeight(scale * v->getLength());
    Stage::gi()->addChild(sb);
    Keyboard::gi()->addEventListener(this);
}

void InitState::focus()
{
    Console::print("FOCUS");
}

void InitState::tick(double dt)
{
    static double time = 0;
    time += dt;
    v->tick(dt);
    Vector2D c = v->getCoordinates();
    sb->setX(c.x  * scale);
    sb->setY(c.y * scale);
    sb->setRotationZ(v->getAngle());
    Console::print(v->getSpeed());
}

void InitState::Invoke(const Event &event)
{
    if (event.type == KeyboardEvent::KEY_DOWN)
    {
        KeyboardEvent* st = (KeyboardEvent*)(&event);
        switch (st->keyCode)
        {
            case Qt::Key_Up:
            {
                v->setAccelerationState(ForwardAcc);
            } break;
            case Qt::Key_Down:
            {
                    v->setAccelerationState(BackwardAcc);
            } break;
            case Qt::Key_Left:
            {
                v->setRotationPercent(-1);
            } break;
            case Qt::Key_Right:
            {
                    v->setRotationPercent(1);
            } break;
            case Qt::Key_Space:
            {
                    v->setAccelerationState(Brakes);
            } break;
            case Qt::Key_W:
            {
            Console::print("Enter");
                context->changeState(StateEnum::INIT);
            } break;
        }
    }
    else if (event.type == KeyboardEvent::KEY_UP)
    {
        KeyboardEvent* st = (KeyboardEvent*)(&event);
        switch (st->keyCode)
        {
            case Qt::Key_Up:
            {
                    v->setAccelerationState(NoAcc);
            } break;
            case Qt::Key_Down:
            {
                    v->setAccelerationState(NoAcc);
            } break;
            case Qt::Key_Left:
            {
                    v->setRotationPercent(0);
            } break;
            case Qt::Key_Right:
            {
                    v->setRotationPercent(0);
            } break;
            case Qt::Key_Space:
            {
                    v->setAccelerationState(NoAcc);
            } break;
        }
    }
}

void InitState::defocus()
{
}

void InitState::release()
{
    delete v; Stage::gi()->removeChild(sb); Keyboard::gi()->removeEventListener(this); delete sb;
    Console::print("RELEASE");
}

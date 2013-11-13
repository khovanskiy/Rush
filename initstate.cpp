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

InitState::InitState()
{
}

InitState::~InitState()
{
}

void InitState::init()
{
    v = VehicleFactory::createSampleCar(Vector2D(100,100), 0, Vector2D(0, 0), 0);
    v->setTorquePercent(1);
    sb = new Bitmap();
    sb->load(QCoreApplication::applicationDirPath() + "\\DATA\\Textures\\Vehicles\\dodge.jpg");
    sb->setRSPointCenter();
    sb->setScaleX(0.05f);
    sb->setScaleY(0.05f);
    Stage::gi()->addChild(sb);
    Keyboard::gi()->addEventListener(this);
}

void InitState::focus()
{
    Console::print("FOCUS");
}

void InitState::render()
{
    v->tick(0.1);
    Vector2D c = v->getCoordinates();
    sb->setX(c.x);
    sb->setY(c.y);
    sb->setRotationZ(v->getAngle());
}

void InitState::Invoke(const Event &event)
{
    if (event.type == KeyboardEvent::KEY_DOWN)
    {
        KeyboardEvent* st = (KeyboardEvent*)(&event);
        switch (st->keyCode)
        {
            case Qt::Key_W:
            {
                    v->setAccelerationState(ForwardAcc);
            } break;
            case Qt::Key_S:
            {
                    v->setAccelerationState(BackwardAcc);
            } break;
            case Qt::Key_A:
            {
                    v->setRotationPercent(-1);
            } break;
            case Qt::Key_D:
            {
                    v->setRotationPercent(1);
            } break;
            case Qt::Key_Space:
            {
                    v->setAccelerationState(Brakes);
            } break;
        }
    }
    else if (event.type == KeyboardEvent::KEY_UP)
    {
        KeyboardEvent* st = (KeyboardEvent*)(&event);
        switch (st->keyCode)
        {
            case Qt::Key_W:
            {
                    v->setAccelerationState(NoAcc);
            } break;
            case Qt::Key_S:
            {
                    v->setAccelerationState(NoAcc);
            } break;
            case Qt::Key_A:
            {
                    v->setRotationPercent(0);
            } break;
            case Qt::Key_D:
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

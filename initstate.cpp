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
    sb->load(QCoreApplication::applicationDirPath() + "\\DATA\\Textures\\Vehicles\\dodge.png");
    sb->setRSPointCenter();
    sb->setWidth(5 * 1.923);
    sb->setHeight(5 * 5.0);
    Stage::gi()->addChild(sb);
    Keyboard::gi()->addEventListener(this);
}

void InitState::focus()
{
    Console::print("FOCUS");
}

void InitState::render()
{
    static double time = 0;
    time+=0.05;
    v->tick(0.05);
    Vector2D c = v->getCoordinates();
    sb->setX(c.x * 5);
    sb->setY(c.y * 5);
    sb->setRotationZ(v->getAngle());
    Console::print(QVariant(v->getSpeed().getLength()*3.6).toString()+" "+QVariant(time).toString());
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

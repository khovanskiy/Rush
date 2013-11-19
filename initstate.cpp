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

static const double scale = 3;

InitState::InitState()
{
}

InitState::~InitState()
{
}

void InitState::init()
{
    dodge = VehicleFactory::createDodgeChallengerSRT8(Vector2D(20,20), -asin(1), Vector2D(0, 0), 0);
    ferrari = VehicleFactory::createFerrari599GTO(Vector2D(20, 30), -asin(1), Vector2D(0, 0), 0);
    dodge->setTorquePercent(1);
    ferrari->setTorquePercent(1);
    dodge->setAccelerationState(ForwardAcc);
    ferrari->setAccelerationState(ForwardAcc);
    dodgeBitmap = new Bitmap();
    dodgeBitmap->load(QCoreApplication::applicationDirPath() + "\\DATA\\Textures\\Vehicles\\dodge.png");
    dodgeBitmap->setRSPointCenter();
    dodgeBitmap->setWidth(scale * dodge->getWidth());
    dodgeBitmap->setHeight(scale * dodge->getLength());
    ferrariBitmap = new Bitmap();
    ferrariBitmap->load(QCoreApplication::applicationDirPath() + "\\DATA\\Textures\\Vehicles\\ferrari.png");
    ferrariBitmap->setRSPointCenter();
    ferrariBitmap->setWidth(scale * ferrari->getWidth());
    ferrariBitmap->setHeight(scale * ferrari->getLength());
    Stage::gi()->addChild(dodgeBitmap);
    Stage::gi()->addChild(ferrariBitmap);
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
    dodge->tick(dt);
    ferrari->tick(dt);
    Vector2D dodge_c = dodge->getCoordinates();
    dodgeBitmap->setX(dodge_c.x  * scale);
    dodgeBitmap->setY(dodge_c.y * scale);
    dodgeBitmap->setRotationZ(dodge->getAngle());
    Vector2D ferrari_c = ferrari->getCoordinates();
    ferrariBitmap->setX(ferrari_c.x  * scale);
    ferrariBitmap->setY(ferrari_c.y * scale);
    ferrariBitmap->setRotationZ(ferrari->getAngle());
    Console::print(dodge->getSpeed());
    //Console::print(dodge->isStaying());
    Console::print(ferrari->getSpeed());
    Console::print(time);
    Console::print(QCoreApplication::applicationDirPath());
    //Console::print(ferrari->isStaying());
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
                dodge->setAccelerationState(ForwardAcc);
            } break;
            case Qt::Key_Down:
            {
                dodge->setAccelerationState(BackwardAcc);
            } break;
            case Qt::Key_Left:
            {
                dodge->setRotationPercent(-1);
            } break;
            case Qt::Key_Right:
            {
                    dodge->setRotationPercent(1);
            } break;
            case Qt::Key_Space:
            {
                    dodge->setAccelerationState(Brakes);
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
                    dodge->setAccelerationState(NoAcc);
            } break;
            case Qt::Key_Down:
            {
                    dodge->setAccelerationState(NoAcc);
            } break;
            case Qt::Key_Left:
            {
                    dodge->setRotationPercent(0);
            } break;
            case Qt::Key_Right:
            {
                    dodge->setRotationPercent(0);
            } break;
            case Qt::Key_Space:
            {
                    dodge->setAccelerationState(NoAcc);
            } break;
        }
    }
}

void InitState::defocus()
{
}

void InitState::release()
{
    delete dodge;
    delete ferrari;
    Stage::gi()->removeChild(dodgeBitmap);
    Stage::gi()->removeChild(ferrariBitmap);
    Keyboard::gi()->removeEventListener(this);
    delete dodgeBitmap;
    delete ferrariBitmap;
    Console::print("RELEASE");
}

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
    v->setAccelerationState(ForwardAcc);
    v->setRotationPercent(0.4);
    v->setTorquePercent(1);
    sb = new Bitmap();
    sb->load(QCoreApplication::applicationDirPath() + "\\DATA\\Textures\\Vehicles\\dodge.jpg");
    sb->setRSPointCenter();
    sb->setScaleX(0.02f);
    sb->setScaleY(0.02f);
    Stage::gi()->addChild(sb);
    Keyboard::gi()->addEventListener(this);
    v->tick(0.01);
}

void InitState::focus()
{
    Console::print("FOCUS");
}

void InitState::render()
{
    static double time = 0;
    //v->setAccelerationState(ForwardAcc);
    //v->setRotationPercent(1);
    //v->setTorquePercent(1);
    v->tick(0.05);
    time += 0.05;
    if (time > 5)
    {
        v->setRotationPercent(-0.6);
    }
    if (time > 20)
    {
        v->setAccelerationState(Brakes);
    }
    if (time > 25)
    {
        v->setAccelerationState(BackwardAcc);
        v->setRotationPercent(0.3);
    }
    Vector2D c = v->getCoordinates();
    sb->setX(c.x / 4);
    sb->setY(c.y / 4);
    sb->setRotationZ(v->getAngle() / 2);
    //Console::print("Gear:");
    //Console::print(v->getGear());
    //Console::print("Spins per minute");
    //Console::print(v->getSpins());
    //Console::print(time);
}

void InitState::Invoke(const Event &event)
{
    if (event.type == KeyboardEvent::KEY_UP)
    {
        context->changeState(StateEnum::INIT);
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

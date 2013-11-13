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
    v = VehicleFactory::createSampleCar(Vector2D(100,100), 0, Vector2D(50,50), 10);
    sb = new Bitmap();
    sb->load(QCoreApplication::applicationDirPath() + "\\DATA\\Textures\\Vehicles\\dodge.jpg");
    sb->setRSPointCenter();
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
    v->setAccelerationState(ForwardAcc);
    v->setTorquePercent(1);
    Vector2D c = v->getCoordinates();
    sb->setX(c.x);
    sb->setY(c.y);
    sb->setRotationZ(v->getAngle());
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

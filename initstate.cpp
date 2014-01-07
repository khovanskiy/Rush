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

static const double scale = 5;
static const int FREE_VIEW = 0;
static const int FIXED_COORDINATES_FIXED_ANGLE = 1;
static const int FIXED_COORDINATES = 2;
static const int TOTAL_VIEWS = 3;
static int view = 0;

InitState::InitState()
{
}

InitState::~InitState()
{
}

void InitState::init()
{
    dodge = VehicleFactory::createDodgeChallengerSRT8();
    dodge->setCoordinates(Vector2D(5, 0));
    dodge->setAngle(2 * asin(1));
    dodge->setTorquePercent(1);
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            Vehicle* ferrari = VehicleFactory::createFerrari599GTO();
            ferrari->setCoordinates(Vector2D(5 + 6 * j, -15 - 5 * i));
            ferrari->setAngle(-asin(1));
            /*AABB aabb = ferrari->getAABB();
            Console::print("Ferrari");
            Console::print(Vector2D(aabb.left, aabb.right));
            Console::print(Vector2D(aabb.bottom, aabb.top));/**/
        }
    }/**/
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
    PhysicsWorld::getInstance().tick(dt);
    std::vector<PhysicsObject*> new_objects = PhysicsWorld::getInstance().popNewObjects();
    for (auto i = new_objects.begin(); i != new_objects.end(); i++)
    {
        PhysicsObject* object = (*i);
        Bitmap* bitmap = new Bitmap();
        std::string type = object->getType();
        QString path = QCoreApplication::applicationDirPath();
        if (type == "DodgeChallengerSRT8")
        {
            path.append("\\DATA\\Textures\\Vehicles\\dodge_small.png");
        }
        else if (type == "Ferrari599GTO")
        {
            path.append("\\DATA\\Textures\\Vehicles\\ferrari_small.png");
        }
        bitmap->load(path);
        bitmap->setRSPointCenter();
        bitmap->setWidth(scale * object->getWidth());
        bitmap->setHeight(scale * object->getHeight());
        Stage::gi()->addChild(bitmap);
        game_objects.push_back(std::pair<Bitmap*, PhysicsObject*>(bitmap, object));
    }
    static Vector2D center(500, 500);
    static Vector2D dr(0, 0);
    static double d_angle = 0;
    switch (view)
    {
    case FIXED_COORDINATES:
    {
        dr = dodge->getCoordinates();
    } break;
    case FIXED_COORDINATES_FIXED_ANGLE:
    {
        dr = dodge->getCoordinates();
        d_angle = 2 * asin(1) + dodge->getAngle();
    } break;
    }
    for (auto i = game_objects.begin(); i != game_objects.end(); i++)
    {
        Vector2D r = i->second->getCoordinates();
        r.sub(dr);
        r.rotate(-d_angle);
        r.mul(scale);
        r.add(center);
        i->first->setX(r.x);
        i->first->setY(r.y);
        i->first->setRotationZ(i->second->getAngle() - d_angle);
    }/**/
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
            case Qt::Key_Q:
            {
                Console::print("Changed view.");
                view = (view + 1) % TOTAL_VIEWS;
            }
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
    Keyboard::gi()->removeEventListener(this);
    for (auto i = game_objects.begin(); i != game_objects.end(); i++)
    {
        Stage::gi()->removeChild(i->first);
        delete i->first;
    }
    PhysicsWorld::getInstance().clear();
    game_objects.clear();
    Console::print("RELEASE");
}

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
static const int FREE_VIEW = 0;
static const int FIXED_COORDINATES_FIXED_ANGLE = 1;
static const int FIXED_COORDINATES = 2;
static const int TOTAL_VIEWS = 3;
static int view = 0;
static Vector2D mouse_pointer(0, 0);
static Vector2D r_center(500, 500);
static Vector2D dr(0, 0);
static double d_angle = 0;
static bool firing = false;

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
    Turret turret;
    turret.setFireDelay(0.25);
    //turret.setMaxAngle(asin(1));
    turret.setMaxAngle(0);
    turret.setPosition(Vector2D(0, 0));
    turret.setBullet(10, 50, BulletType::Simple);
    dodge->addTurret(turret);
    turret.setPosition(Vector2D(-0.5, 0));
    dodge->addTurret(turret);
    turret.setPosition(Vector2D(0.5, 0));
    dodge->addTurret(turret);
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            Vehicle* ferrari = VehicleFactory::createFerrari599GTO();
            ferrari->setCoordinates(Vector2D(5 + 6 * j, -15 - 5 * i));
            ferrari->setAngle(-asin(1));
        }
    }
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
    std::vector<std::pair<Bitmap*, PhysicsObject*>> remained;
    for (auto i = game_objects.begin(); i != game_objects.end(); i++)
    {
        if (i->second->isValid())
        {
            remained.push_back(*i);
        }
        else
        {
            Stage::gi()->removeChild(i->first);
            delete i->first;
        }
    }
    game_objects = remained;
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
        else if (type == "Bullet")
        {
            Bullet* bullet = dynamic_cast<Bullet*>(object);
            switch (bullet->bullet_type)
            {
            case BulletType::Simple:
            default:
                path.append("\\DATA\\Textures\\Bullets\\bullet.png");
                break;
            }
        }
        bitmap->load(path);
        bitmap->setRSPointCenter();
        bitmap->setWidth(scale * object->getWidth());
        bitmap->setHeight(scale * object->getHeight());
        Stage::gi()->addChild(bitmap);
        game_objects.push_back(std::pair<Bitmap*, PhysicsObject*>(bitmap, object));
    }
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
        r.add(r_center);
        i->first->setX(r.x);
        i->first->setY(r.y);
        i->first->setRotationZ(i->second->getAngle() - d_angle);
    }/**/
}

void InitState::Invoke(const Event &event)
{
    if (event.type == MouseEvent::CLICK)
    {
        MouseEvent* me = (MouseEvent*) (&event);
        firing = !firing;
        Vector2D r = dodge->getCoordinates();
        r.sub(dr);
        r.rotate(-d_angle);
        r.mul(scale);
        r.add(r_center);
        int xr = me->getX() - r.x;
        int yr = me->getY() - r.y;
        double angle = atan2(yr, xr);
        dodge->setFiring(firing, angle);
        //Console::print(Vector2D(me->getX(), me->getY()));
    }
    else if (event.type == KeyboardEvent::KEY_DOWN)
    {
        KeyboardEvent* st = (KeyboardEvent*)(&event);
        switch (st->keyCode)
        {
            case Qt::Key_W:
            {
                dodge->setAccelerationState(ForwardAcc);
            } break;
            case Qt::Key_S:
            {
                dodge->setAccelerationState(BackwardAcc);
            } break;
            case Qt::Key_A:
            {
                dodge->setRotationPercent(-1);
            } break;
            case Qt::Key_D:
            {
                    dodge->setRotationPercent(1);
            } break;
            case Qt::Key_Space:
            {
                    dodge->setAccelerationState(Brakes);
            } break;
            case Qt::Key_Escape:
            {
            //Console::print("Enter");
                context->changeState(StateEnum::INIT);
            } break;
            case Qt::Key_Q:
            {
                //Console::print("Changed view.");
                view = (view + 1) % TOTAL_VIEWS;
            }
        }
    }
    else if (event.type == KeyboardEvent::KEY_UP)
    {
        KeyboardEvent* st = (KeyboardEvent*)(&event);
        switch (st->keyCode)
        {
            case Qt::Key_W:
            {
                    dodge->setAccelerationState(NoAcc);
            } break;
            case Qt::Key_S:
            {
                    dodge->setAccelerationState(NoAcc);
            } break;
            case Qt::Key_A:
            {
                    dodge->setRotationPercent(0);
            } break;
            case Qt::Key_D:
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
    //Console::print("RELEASE");
}

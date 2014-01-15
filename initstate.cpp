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
#include "mouse.h"
#include "keyboardevent.h"
#include "random"
#include "QCoreApplication"
#include "physicsobjectfactory.h"

static double scale = 15;
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
static double alpha = 0;

InitState::InitState()
{    
}

InitState::~InitState()
{
}

void InitState::init()
{
    time = 0;
    dodge = PhysicsObjectFactory::createVehicle(Vehicle::DODGE_CHALLENGER_SRT8);
    dodge->setCoordinates(Vector2D(5, 0));
    dodge->setAngle(2 * asin(1));
    dodge->setTorquePercent(1);
    Turret * turret = PhysicsObjectFactory::createVehicleTurret(Turret::SAW);
    turret->setPosition(Vector2D(-0.5, 2.2));
    dodge->addTurret(turret);
    turret = PhysicsObjectFactory::createVehicleTurret(Turret::SAW);
    turret->setPosition(Vector2D(0.5, 2.2));
    dodge->addTurret(turret);
    turret = PhysicsObjectFactory::createVehicleTurret(Turret::MACHINEGUN);
    turret->setPosition(Vector2D(0.5, 1));
    dodge->addTurret(turret);
    turret = PhysicsObjectFactory::createVehicleTurret(Turret::MACHINEGUN);
    turret->setPosition(Vector2D(-0.5, 1));
    dodge->addTurret(turret);
    turret = PhysicsObjectFactory::createVehicleTurret(Turret::ROCKET_LAUNCHER);
    turret->setPosition(Vector2D(0, -0.5));
    dodge->addTurret(turret);/**/
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            Vehicle* ferrari = PhysicsObjectFactory::createVehicle(Vehicle::FERRARI_599GTO);
            ferrari->setCoordinates(Vector2D(50 + 6 * j, -15 - 5 * i));
            ferrari->setAngle(-asin(1));
        }
    }/**/
    /*for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            Obstacle* obstacle = PhysicsObjectFactory::createObstacle(
                        Vector2D(5 + 2 * j, -15 - 5 * i), 0, Obstacle::STONE_WALL);
        }
    }/**/
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            PhysicsObjectFactory::createObstacle(Vector2D(5 + 2 * j, -15 - 2 * i), 0, Obstacle::WOODEN_BARREL);
        }
    }/**/
    Keyboard::gi()->addEventListener(this);
    Mouse::gi()->addEventListener(this);
}

void InitState::focus()
{
    Console::print("FOCUS");
}

void InitState::addGameObject(GameObject *game_object)
{
    game_objects.push_back(game_object);
    addAllBitmaps(game_object);
}

void InitState::addPhysicsObject(ObjectData *object_data)
{
    addGameObject(new GameObject(object_data));
}

void InitState::addAllBitmaps(GameObject *game_object)
{
    Stage::gi()->addChild(game_object->bitmap);
    std::vector<GameObject*> inner_objects = game_object->getInnerObjects();
    for (auto i = inner_objects.begin(); i != inner_objects.end(); i++)
    {
        addAllBitmaps(*i);
    }
}

void InitState::removeAllBitmaps(GameObject *game_object)
{
    Stage::gi()->removeChild(game_object->bitmap);
    std::vector<GameObject*> inner_objects = game_object->getInnerObjects();
    for (auto i = inner_objects.begin(); i != inner_objects.end(); i++)
    {
        removeAllBitmaps(*i);
    }
}


void InitState::getNewPhysicsObjects()
{
    std::vector<ObjectData*> new_objects = PhysicsWorld::gi().popNewObjects();
    for (auto i = new_objects.begin(); i != new_objects.end(); i++)
    {
        addPhysicsObject(*i);
    }
}

void InitState::renewGameObjects()
{
    std::vector<GameObject*> remained;
    for (auto i = game_objects.begin(); i != game_objects.end(); i++)
    {
        if ((*i)->object_data->object->isValid())
        {
            remained.push_back(*i);
        }
        else
        {
            removeAllBitmaps(*i);
            delete *i;
        }
    }
    game_objects = remained;
    switch (view)
    {
    case FIXED_COORDINATES:
    {
        dr = dodge->getCoordinates().getMul(-1);
    } break;
    case FIXED_COORDINATES_FIXED_ANGLE:
    {
        dr = dodge->getCoordinates().getMul(-1);
        d_angle = -2 * asin(1) - dodge->getAngle();
    } break;
    }
    for (auto i = game_objects.begin(); i != game_objects.end(); i++)
    {
        (*i)->update(scale, d_angle, dr, r_center);
    }
}

void InitState::tick(double dt)
{
    time += dt;
    PhysicsWorld::gi().tick(dt);
    getNewPhysicsObjects();
    renewGameObjects();
    Console::print(time);/**/
}

void InitState::Invoke(const Event &event)
{
    if (event.target == Mouse::gi())
    {
        if ((event.type == MouseEvent::MOUSE_DOWN))
        {
            firing = true;
        }
        else if (event.type == MouseEvent::MOUSE_UP)
        {
            firing = false;
        }
        else if (event.type == MouseEvent::MOUSE_MOVE)
        {
            MouseEvent* me = (MouseEvent*)(&event);
            mouse_pointer = Vector2D(me->getX(), me->getY());
            //Console::print(mouse_pointer);
        }
        Vector2D r = dodge->getMassCenter();
        r.add(dr);
        r.rotate(d_angle);
        r.mul(scale);
        r.add(r_center);
        double dy = mouse_pointer.y - r.y;
        double dx = mouse_pointer.x - r.x;
        alpha = -asin(1) +atan2(dy, dx) - dodge->getAngle() - d_angle;
        dodge->setFiring(firing, alpha);
    }
    else if (event.target == Keyboard::gi())
    {
        if (event.type == KeyboardEvent::KEY_DOWN)
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
                    context->changeState(StateEnum::INIT);
                } break;
                case Qt::Key_Q:
                {
                    view = (view + 1) % TOTAL_VIEWS;
                } break;
                case Qt::Key_Plus:
                {
                    scale *= 1.5;
                } break;
                case Qt::Key_Equal:
                {
                    scale *= 1.5;
                } break;
                case Qt::Key_Minus:
                {
                    scale /= 1.5;
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
}

void InitState::defocus()
{
}

void InitState::release()
{
    Keyboard::gi()->removeEventListener(this);
    Mouse::gi()->removeEventListener(this);
    for (auto i = game_objects.begin(); i != game_objects.end(); i++)
    {
        removeAllBitmaps(*i);
        delete *i;
    }
    PhysicsWorld::gi().clear();
    game_objects.clear();
}

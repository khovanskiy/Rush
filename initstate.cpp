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
<<<<<<< HEAD
#include "vehiclefactory.h"
#include "gameobject.h"
#include "view.h"
#include "interface.h"
#include "mouse.h"

static const double scale = 25;
=======
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
>>>>>>> origin/physicsDebug

InitState::InitState()
{    
}

InitState::~InitState()
{
}

void InitState::init()
{
<<<<<<< HEAD
    View* v = new View();
    Bitmap* t = new Bitmap();
    t->load(QCoreApplication::applicationDirPath() + "\\DATA\\Textures\\Turrets\\1.png");
    v->addChild(t);
    v->setX(-100);
    t->setX(100);
    t->setY(200);
    Interface::gi()->addChild(v);

    dodge = VehicleFactory::createDodgeChallengerSRT8(Vector2D(20,20), -asin(1), Vector2D(0, 0), 0);
    ferrari = VehicleFactory::createFerrari599GTO(Vector2D(20, 30), -asin(1), Vector2D(0, 0), 0);
    current = dodge;
    dodge->setTorquePercent(1);
    ferrari->setTorquePercent(1);
    //dodge->setAccelerationState(ForwardAcc);
    //ferrari->setAccelerationState(ForwardAcc);

    dodgeBitmap = new Bitmap();
    dodgeBitmap->load(QCoreApplication::applicationDirPath() + "\\DATA\\Textures\\Vehicles\\dodge.png");
    dodgeBitmap->setRSPointCenter();
    dodgeBitmap->setWidth(scale * dodge->getWidth());
    dodgeBitmap->setHeight(scale * dodge->getLength());
    dodgeBitmap->addEventListener(this);

    ferrariBitmap = new Bitmap();
    ferrariBitmap->load(QCoreApplication::applicationDirPath() + "\\DATA\\Textures\\Vehicles\\ferrari.png");
    ferrariBitmap->setRSPointCenter();
    ferrariBitmap->setWidth(scale * ferrari->getWidth());
    ferrariBitmap->setHeight(scale * ferrari->getLength());
    ferrariBitmap->addEventListener(this);

    Stage::gi()->addChild(dodgeBitmap);
    Stage::gi()->addChild(ferrariBitmap);

    Mouse::gi()->addEventListener(this);
    Keyboard::gi()->addEventListener(this);

=======
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
    /*for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            Vehicle* ferrari = PhysicsObjectFactory::createVehicle(Vehicle::FERRARI_599GTO);
            ferrari->setCoordinates(Vector2D(5 + 6 * j, -15 - 5 * i));
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
        }
    Keyboard::gi()->addEventListener(this);
    Mouse::gi()->addEventListener(this);
>>>>>>> origin/physicsDebug
}

void InitState::focus()
{
    Console::print("FOCUS");
}

<<<<<<< HEAD
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
    //Console::print(dodge->getSpeed());
    //Console::print(dodge->isStaying());
    //Console::print(ferrari->getSpeed());
   // Console::print(time);
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
                current->setAccelerationState(ForwardAcc);
            } break;
            case Qt::Key_Down:
            {
                current->setAccelerationState(BackwardAcc);
            } break;
            case Qt::Key_Left:
            {
                current->setRotationPercent(-1);
            } break;
            case Qt::Key_Right:
            {
                    current->setRotationPercent(1);
            } break;
            case Qt::Key_Space:
            {
                    current->setAccelerationState(Brakes);
            } break;
            case Qt::Key_W:
            {
            Console::print("Enter");
                context->changeState(StateEnum::INIT);
            } break;
        case Qt::Key_Escape:
        {
            context->changeState(StateEnum::EXIT);
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
                    current->setAccelerationState(NoAcc);
            } break;
            case Qt::Key_Down:
            {
                    current->setAccelerationState(NoAcc);
            } break;
            case Qt::Key_Left:
            {
                    current->setRotationPercent(0);
            } break;
            case Qt::Key_Right:
            {
                    current->setRotationPercent(0);
            } break;
            case Qt::Key_Space:
            {
                    current->setAccelerationState(NoAcc);
            } break;
        }
    }
    else if (event.type == MouseEvent::MOUSE_OVER)
    {
        if (event.target == ferrariBitmap)
        {
            Console::print("Over ferrari");
        }
    }
    else if (event.type == MouseEvent::MOUSE_OUT)
    {
        if (event.target == ferrariBitmap)
        {
            Console::print("Out ferrari");
        }
    }
    else if (event.type == MouseEvent::MOUSE_DOWN)
    {
        if (event.target == Mouse::gi())
        Console::print("Mouse down");
    }
    else if (event.type == MouseEvent::MOUSE_UP)
    {
        if (event.target == Mouse::gi())
        Console::print("Mouse up");
    }
    else if (event.type == MouseEvent::CLICK)
    {
        if (event.target == ferrariBitmap)
        {
            current = ferrari;
        }
        else if (event.target == dodgeBitmap)
        {
            current = dodge;
=======
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
    Console::print(time);/**/
}

void InitState::tick(double dt)
{
    time += dt;
    PhysicsWorld::gi().tick(dt);
    getNewPhysicsObjects();
    renewGameObjects();
}

void InitState::Invoke(const Event &event)
{
    if ((event.type == MouseEvent::CLICK) && (event.target == Mouse::gi()))
    {
        static double alpha = 0;
        firing = !firing;
        dodge->setFiring(firing, alpha);
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
>>>>>>> origin/physicsDebug
        }
    }
}

void InitState::defocus()
{
}

void InitState::release()
{
<<<<<<< HEAD
    delete dodge;
    delete ferrari;
    Stage::gi()->removeChild(dodgeBitmap);
    Stage::gi()->removeChild(ferrariBitmap);
    Keyboard::gi()->removeEventListener(this);
    delete dodgeBitmap;
    delete ferrariBitmap;
    Console::print("RELEASE");
=======
    Keyboard::gi()->removeEventListener(this);
    Mouse::gi()->removeEventListener(this);
    for (auto i = game_objects.begin(); i != game_objects.end(); i++)
    {
        removeAllBitmaps(*i);
        delete *i;
    }
    PhysicsWorld::gi().clear();
    game_objects.clear();
>>>>>>> origin/physicsDebug
}

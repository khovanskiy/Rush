#include "gameplaystate.h"

static const double M_PI = 3.14159265358979323846;

#include "thread.h"
#include "random.h"

class Bclass : public Sprite
{

};

class Cclass : public Sprite
{

};

void GameplayState::init()
{
    game_world = new GameWorld();
    physics_world = new PhysicsWorld();

    b = new Bitmap();
    b->load("DATA\\Textures\\Vehicles\\dodge.png");

    /*b->setRSPointCenter();
    b->setPosition(Vector2D(0,0));
    b->setScaleX(1.5);
    b->setScaleY(1.5);
    b->setX(100);

    Console::print("Other");
    Stage::gi()->addChild(b);*/

    car = new Vehicle(new Rectangle2D(Point2D(0,0), 1.962, 4.710), 1887);
    double r[] = {3.59, 2.19, 1.41, 1, 0.83};
    std::vector<double> ratios(r, r + sizeof(r) / sizeof(double));
    car->setEngine(VehicleEngine(637, 6000, ratios, 3.06));
    CarTrack back(-1.62724, 1.604, 1000 / (2 * M_PI * 456), 0.466, true, true, RotationReaction::NoRotation, 0.9, 0.025, 1.5, 1.5, M_PI / 6);
    CarTrack front(1.74552, 1.603, 1000 / (2 * M_PI * 456), 0.544, false, true, RotationReaction::StraightRot, 0.9, 0.025, 1.5, 1.5, M_PI / 6);
    car->setWheels(back, front, 1.45);
    car->setVehicleBody(VehicleBody(0.356, 5.0, 1.923, 1.45, car->chassis.getMassCenter()));
    car->setCoordinates(Vector2D(0, 0));
    car->setAngle(-asin(1));
    car->setTorquePercent(1);



    Turret* t = new Turret(new Rectangle2D(Point2D(0, -0.5), 1.5, 1.5), 100, 7, 0.1, 2 * asin(1), Bullet::BULLET, 0);
    car->addTurret(t);

    game_world->add(car);
    physics_world->add(car);

    Vehicle* car2 = new Vehicle(new Rectangle2D(Point2D(0,0), 1.962, 4.710), 1887);
    car2->setWheels(back, front, 1.45);
    car2->setEngine(VehicleEngine(637, 6000, ratios, 3.06));
    car2->setAngle(M_PI);
    car2->setTorquePercent(0.2);

    car2->setCoordinates(Vector2D(15, 15));

    game_world->add(car2);
    physics_world->add(car2);

    controls = new UIVehicleController(car);

    car->addEventListener(this);

    map_view = new MapView(game_world);

    Mouse::gi()->addEventListener(this);
    Keyboard::gi()->addEventListener(this);
}

void GameplayState::Invoke(const Event &event)
{
    if (event.type == KeyboardEvent::KEY_UP)
    {
        const KeyboardEvent* e = static_cast<const KeyboardEvent*>(&event);
        if (e->keyCode == Qt::Key_Escape)
        {
            context->changeState(StateEnum::GAMEPLAY);
        }
    }
    else if (event.type == "TURRET_FIRE")
    {
        const GameObjectEvent* e = static_cast<const GameObjectEvent*>(&event);
        Vehicle* obj = static_cast<Vehicle*>(event.target);
        Matrix A = obj->getTransform();
        Matrix B = obj->getTurrets()[0]->getTransform();

        Matrix m = Matrix::mul(obj->getTransform(), obj->getTurrets()[0]->getTransform()).invert();
        Vector2D p(0, 1);
        p.rotate(obj->getAngle()+obj->getTurrets()[0]->getAngle());
        p.normalize();
        p.mul(25);

        Bullet* b = new Bullet(m.map(e->v), p, 1, Bullet::BULLET, 0.15, 0.43, 0.05, 3);
        b->setSource(obj);
        game_world->add(b);
        physics_world->add(b);
    }
}

void GameplayState::tick(double dt)
{
    game_world->tick(dt);
    physics_world->tick(dt);
    map_view->update();
    //Vector2D v = car->getCoordinates();
    //Console::print(v);
    //Camera::gi()->setPosition(Vector2D(v.x, v.y));
}

void GameplayState::release()
{
    Keyboard::gi()->removeEventListener(this);
    Mouse::gi()->removeEventListener(this);
    delete controls;
    delete map_view;
    delete physics_world;
    delete game_world;
}

#include "gameplaystate.h"

static const double M_PI = 3.14159265358979323846;

#include "thread.h"
#include "random.h"

void GameplayState::init()
{
    car = new Vehicle(new Rectangle2D(Point2D(0,0), 1.962, 4.710), 1887);
    double r[] = {3.59, 2.19, 1.41, 1, 0.83};
    std::vector<double> ratios(r, r + sizeof(r) / sizeof(double));
    car->setEngine(VehicleEngine(637, 6000, ratios, 3.06));
    CarTrack back(-1.62724, 1.604, 1000 / (2 * M_PI * 456), 0.466, true, true, RotationReaction::NoRotation, 0.9, 0.025, 1.5, 1.5, M_PI / 6);
    CarTrack front(1.74552, 1.603, 1000 / (2 * M_PI * 456), 0.544, false, true, RotationReaction::StraightRot, 0.9, 0.025, 1.5, 1.5, M_PI / 6);
    car->setWheels(back, front, 1.45);
    car->setVehicleBody(VehicleBody(0.356, 5.0, 1.923, 1.45, car->chassis.getMassCenter()));
    car->setCoordinates(Vector2D(10, 10));
    car->setAngle(-asin(1));
    car->setTorquePercent(1);

    Turret* t = new Turret(new Rectangle2D(Point2D(0, -0.5), 1.5, 1.5), 100, 7, 0.1, 2 * asin(1), Bullet::BULLET, 0);
    car->addTurret(t);

    GameWorld::gi().add(car);
    PhysicsWorld::gi().add(car);

    car2 = new Vehicle(new Rectangle2D(Point2D(0,0), 1.962, 4.710), 1887);
    car2->setWheels(back, front, 1.45);
    car2->setEngine(VehicleEngine(637, 6000, ratios, 3.06));
    car2->setAngle(M_PI);
    car2->setTorquePercent(0.2);

    car2->setCoordinates(Vector2D(15, 15));

    GameWorld::gi().add(car2);
    PhysicsWorld::gi().add(car2);

    Mouse::gi()->addEventListener(this);

    UIVehicleController* u = new UIVehicleController(car);

    car->addEventListener(this);

    //Bullet * b = new Bullet(Vector2D(10, 10), Vector2D(1,1), 100, BULLET, 10, 10, 0.001, 1e100);
    //PhysicsWorld::gi().addObject(b);
    map_view = new MapView(&GameWorld::gi());

}

void GameplayState::Invoke(const Event &event)
{
    if (event.type == MouseEvent::MOUSE_MOVE)
    {
        const MouseEvent* e = static_cast<const MouseEvent*>(&event);
    }
    else if (event.type == MouseEvent::MOUSE_DOWN)
    {
        car->setFiring(true);
        //car2->invalidate();
    }
    else if (event.type == MouseEvent::MOUSE_UP)
    {

        car->setFiring(false);
    }
    else if (event.type == "TURRET_FIRE")
    {
        const GameObjectEvent* e = static_cast<const GameObjectEvent*>(&event);
        Console::print("Matrix");
        Vehicle* obj = static_cast<Vehicle*>(event.target);
 /*       QMatrix qm = obj->getTurrets()[0]->getTransform().toQMatrix().inverted() * obj->getTransform().toQMatrix().inverted();
        Console::print(qm);

        QMatrix qm2 = obj->getTurrets()[0]->getTransform().toQMatrix() * obj->getTransform().toQMatrix();
        qm2.inverted();
        Console::print(qm2);

        QMatrix qm3 = obj->getTransform().toQMatrix() * obj->getTurrets()[0]->getTransform().toQMatrix();
        qm3.inverted();
        Console::print(qm3);*/

        Matrix m = Matrix::mul(obj->getTurrets()[0]->getTransform().invert(), obj->getTransform().invert());
/*
        Matrix m2 = Matrix::mul(obj->getTurrets()[0]->getTransform(), obj->getTransform());
        m2.invert();

        Matrix m3 = Matrix::mul(obj->getTransform(), obj->getTurrets()[0]->getTransform());
        m3.invert();

        Console::print(m);
        Console::print(m2);
        Console::print(m3);

        Console::print(m);
        Console::print(m.invert().invert());*/
        //m.invert();
        Bullet* b = new Bullet(m.map(e->v), m.map(e->v), 1, Bullet::BULLET, 0.15, 0.43, 0.05, 3);
        b->setSource(obj);
        GameWorld::gi().add(b);
        PhysicsWorld::gi().add(b);

    }
}

void GameplayState::tick(double dt)
{
    GameWorld::gi().tick(dt);
    PhysicsWorld::gi().tick(dt);
}

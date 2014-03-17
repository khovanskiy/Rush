#include "gameplaystate.h"

static const double M_PI = 3.14159265358979323846;

#include "thread.h"
#include "random.h"

void GameplayState::init()
{
    Bitmap* bg = new Bitmap();
    bg->load("../../../../coin.png");
    bg->setScaleX(70);
    bg->setScaleY(50);
    //bg->setX(100);
    //bg->setY(100);
    Background::gi()->addChild(bg);

    car = new Vehicle(new Rectangle2D(Point2D(0,0), 1.962, 4.710), 1887);



    //1887 * (1.923 * 1.923 + 4.710 * 4.710) / 12

    double r[] = {3.59, 2.19, 1.41, 1, 0.83};
    std::vector<double> ratios(r, r + sizeof(r) / sizeof(double));
    car->setEngine(VehicleEngine(637, 6000, ratios, 3.06));

    CarTrack back(-1.62724, 1.604, 1000 / (2 * M_PI * 456), 0.466, true, true, RotationReaction::NoRotation, 0.9, 0.025, 1.5, 1.5, M_PI / 6);
    CarTrack front(1.74552, 1.603, 1000 / (2 * M_PI * 456), 0.544, false, true, RotationReaction::StraightRot, 0.9, 0.025, 1.5, 1.5, M_PI / 6);
    car->setWheels(back, front, 1.45);

    car->setVehicleBody(VehicleBody(0.356, 5.0, 1.923, 1.45, car->chassis.getMassCenter()));

    car->setCoordinates(Vector2D(10, 10));
    //car->setRotationPercent(-asin(1));
    car->setAngle(-asin(1));
    car->setTorquePercent(1);

    //car->setAccelerationState(AccelerationState::ForwardAcc);

    PhysicsWorld::gi().addObject(car);

    car2 = new Vehicle(new Rectangle2D(Point2D(0,0), 1.962, 4.710), 1887);
    car2->setWheels(back, front, 1.45);
    car2->setEngine(VehicleEngine(637, 6000, ratios, 3.06));
    car2->setAngle(M_PI);
    car2->setTorquePercent(0.2);
    //car2->setAccelerationState(AccelerationState::ForwardAcc);

    //Console::print(car2->getId());
    Turret* t = new Turret(new Rectangle2D(Point2D(0, -1.5), 1.5, 1.5), 100, 7, 0.1, 2 * asin(1), Bullet::BULLET, 0);
    car->addTurret(t);
    Turret* t2 = new Turret(new Rectangle2D(Point2D(0, 1.5), 1.5, 1.5), 100, 7, 0.1, 2 * asin(1), Bullet::BULLET, 0);
    car->addTurret(t2);

    //PhysicsWorld::gi().addObject(t);
    car2->setCoordinates(Vector2D(30, 10));

    b = new VehicleView(car);
    Stage::gi()->addChild(b);

    b2 = new VehicleView(car2);
    Stage::gi()->addChild(b2);


    PhysicsWorld::gi().addObject(car2);

    Mouse::gi()->addEventListener(this);

    UIVehicleController* u = new UIVehicleController(car);
    point = new Bitmap();
    point->load("DATA\\Textures\\Vehicles\\dodge.png");
    //Stage::gi()->addChild(point);

    point->setInter(true);
    point->setX(300);
    point->setY(400);
}

void GameplayState::Invoke(const Event &event)
{
    if (event.type == MouseEvent::MOUSE_MOVE)
    {
        const MouseEvent* e = static_cast<const MouseEvent*>(&event);
        Vector2D v(200, 100);
        //Console::print(v);
        Matrix m;
        //car2->turretsToPoint(v);
    }
}

void GameplayState::tick(double dt)
{
    //car->turretsToPoint();
    PhysicsWorld::gi().tick(dt);
    //point->setRotationZ(point->getRotationZ()+1);
    //car2->setAngle(car2->getAngle()+2.9f);
    //q->setRotationZ(q->getRotationZ()+1.9f);
}

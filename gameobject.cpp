#include "gameobject.h"
#include "stage.h"
#include <QCoreApplication>

GameObject::GameObject(PhysicsObject *object)
{
    bitmap = new Bitmap();
    physics_object = object;
    QString type = object->getType();
    QString path = QCoreApplication::applicationDirPath();
    if (type == PhysicsObject::VEHICLE)
    {
        Vehicle* vehicle = dynamic_cast<Vehicle*>(object);
        QString model = vehicle->getCarModel();
        if (model == Vehicle::DODGE_CHALLENGER_SRT8)
        {
            bitmap->load(path + "\\DATA\\Textures\\Vehicles\\dodge_small.png");
        }
        else if (model == Vehicle::FERRARI_599GTO)
        {
            bitmap->load(path + "\\DATA\\Textures\\Vehicles\\ferrari_small.png");
        }
        std::vector<Turret*> turrets = vehicle->getTurrets();
        for (auto j = turrets.begin(); j != turrets.end(); j++)
        {
            inner_objects.push_back(new GameObject(*j));
        }
    }
    else if (type == PhysicsObject::BULLET)
    {
        QString bullet_type = dynamic_cast<Bullet*>(object)->getBulletType();
        if (bullet_type == Bullet::BULLET)
        {
            bitmap->load(path + "\\DATA\\Textures\\Bullets\\bullet.png");
        }
        else if (bullet_type == Bullet::MISSILE)
        {
            bitmap->load(path + "\\DATA\\Textures\\Bullets\\missile.png");
        }
        else if (bullet_type == Bullet::CUT)
        {
            bitmap->load(path + "\\DATA\\Textures\\Bullets\\cut.png");
        }
    }
    else if (type == PhysicsObject::EXPLOSION)
    {
        bitmap->load(path + "\\DATA\\Textures\\Bullets\\explosion.png");
    }
    else if (type == PhysicsObject::TURRET)
    {
        QString turret_type = dynamic_cast<Turret*>(object)->getTurretType();
        if (turret_type == Turret::MACHINEGUN)
        {
            bitmap->load(path + "\\DATA\\Textures\\Turrets\\machinegun.png");
        }
        else if (turret_type == Turret::ROCKET_LAUNCHER)
        {
            bitmap->load(path + "\\DATA\\Textures\\Turrets\\rocket_launcher.png");
        }
        else if (turret_type == Turret::SAW)
        {
            bitmap->load(path + "\\DATA\\Textures\\Turrets\\saw.png");
        }
    }
    bitmap->setRSPointCenter();
}

GameObject::~GameObject()
{
    for (auto i = inner_objects.begin(); i != inner_objects.end(); i++)
    {
        delete *i;
    }
    delete bitmap;
}

void GameObject::update(double scale, double angle, Vector2D dr, Vector2D center)
{
    Vector2D r = physics_object->getMassCenter();
    r.add(dr);
    r.rotate(angle);
    r.mul(scale);
    r.add(center);
    bitmap->setWidth(scale * physics_object->getWidth());
    bitmap->setHeight(scale * physics_object->getHeight());
    bitmap->setX(r.x);
    bitmap->setY(r.y);
    if (physics_object->getType() != PhysicsObject::EXPLOSION)
    {
        bitmap->setRotationZ(physics_object->getAngle() + angle);
    }
    for (auto i = inner_objects.begin(); i != inner_objects.end(); i++)
    {
        (*i)->update(scale, angle, dr, center);
    }
}

std::vector<GameObject*> GameObject::getInnerObjects()
{
    return this->inner_objects;
}


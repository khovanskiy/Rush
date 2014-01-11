#include "gameobject.h"
<<<<<<< HEAD

std::map<__int64, GameObject*> GameObject::table;

GameObject::GameObject(__int64 id)
{
    insert(id, this);
=======
#include "stage.h"
#include <QCoreApplication>

static const double collision_damage_koef = 2e-2;
static const double bullet_damage_koef = 0.2;
static const double explosion_damage_koef = 1;
static const double minimum_damaging_impulse = 1000;

GameObject::GameObject(ObjectData *object_data)
{
    this->bitmap = new Bitmap();
    this->object_data = object_data;
    PhysicsObject* object = object_data->object;
    QString type = object->getType();
    QString path = QCoreApplication::applicationDirPath();
    if (type == PhysicsObject::VEHICLE)
    {
        Vehicle* vehicle = dynamic_cast<Vehicle*>(object);
        QString model = vehicle->getVehicleType();
        if (model == Vehicle::DODGE_CHALLENGER_SRT8)
        {
            bitmap->load(path + "\\DATA\\Textures\\Vehicles\\dodge_small.png");
            health = 1000;
        }
        else if (model == Vehicle::FERRARI_599GTO)
        {
            bitmap->load(path + "\\DATA\\Textures\\Vehicles\\ferrari_small.png");
            health = 1000;
        }
        std::vector<Turret*> turrets = vehicle->getTurrets();
        for (auto j = turrets.begin(); j != turrets.end(); j++)
        {
            inner_objects.push_back(new GameObject(new ObjectData(*j)));
        }
    }
    else if (type == PhysicsObject::BULLET)
    {
        QString bullet_type = dynamic_cast<Bullet*>(object)->getBulletType();
        if (bullet_type == Bullet::BULLET)
        {
            bitmap->load(path + "\\DATA\\Textures\\Bullets\\bullet.png");
            health = 1000;
        }
        else if (bullet_type == Bullet::MISSILE)
        {
            bitmap->load(path + "\\DATA\\Textures\\Bullets\\missile.png");
            health = 1000;
        }
        else if (bullet_type == Bullet::CUT)
        {
            bitmap->load(path + "\\DATA\\Textures\\Bullets\\cut.png");
            health = 1000;
        }
    }
    else if (type == PhysicsObject::EXPLOSION)
    {
        bitmap->load(path + "\\DATA\\Textures\\Bullets\\explosion.png");
        health = 1000;
    }
    else if (type == PhysicsObject::TURRET)
    {
        QString turret_type = dynamic_cast<Turret*>(object)->getTurretType();
        if (turret_type == Turret::MACHINEGUN)
        {
            bitmap->load(path + "\\DATA\\Textures\\Turrets\\machinegun.png");
            health = 1000;
        }
        else if (turret_type == Turret::ROCKET_LAUNCHER)
        {
            bitmap->load(path + "\\DATA\\Textures\\Turrets\\rocket_launcher.png");
            health = 1000;
        }
        else if (turret_type == Turret::SAW)
        {
            bitmap->load(path + "\\DATA\\Textures\\Turrets\\saw.png");
            health = 1000;
        }
    }
    else if (type == PhysicsObject::OBSTACLE)
    {
        QString obstacle_type = dynamic_cast<Obstacle*>(object)->getObstacleType();
        if (obstacle_type == Obstacle::STONE_WALL)
        {
            bitmap->load(path + "\\DATA\\Textures\\Obstacles\\stone_wall.png");
            health = 1e100;
        }
        else if (obstacle_type == Obstacle::WOODEN_BARREL)
        {
            bitmap->load(path + "\\DATA\\Textures\\Obstacles\\wooden_barrel.png");
            health = 100;
        }
        else if (obstacle_type == Obstacle::WOODEN_BOX)
        {
            bitmap->load(path + "\\DATA\\Textures\\Obstacles\\wooden_box.png");
            health = 100;
        }
    }
    bitmap->setRSPointCenter();
>>>>>>> origin/physicsDebug
}

GameObject::~GameObject()
{
<<<<<<< HEAD
    erase(this->my_id);
}

__int64 GameObject::getId()
{
    return this->my_id;
}

void GameObject::insert(__int64 id, const GameObject * obj)
{
    this->my_id = id;
    table[id] = this;
}

void GameObject::erase(__int64 id)
{
    std::map<__int64, GameObject*>::iterator i = table.find(id);
    if (i != table.end())
    {
        table.erase(i);
    }
}

void GameObject::setId(__int64 id)
{
    if (findById(id) == 0)
    {
        erase(id);
        erase(my_id);
        insert(id, this);
    }
}

GameObject* GameObject::findById(__int64 id)
{
    GameObject* result = 0;
    std::map<__int64, GameObject*>::iterator i = table.find(id);
    if (i != table.end())
    {
        result = i->second;
    }
    return result;
}
=======
    for (auto i = inner_objects.begin(); i != inner_objects.end(); i++)
    {
        delete *i;
    }
    delete bitmap;
}

void GameObject::update(double scale, double angle, Vector2D dr, Vector2D center)
{
    PhysicsObject* physics_object = object_data->object;
    Vector2D r = physics_object->getMassCenter();
    r.add(dr);
    r.rotate(angle);
    r.mul(scale);
    r.add(center);
    bitmap->setWidth(scale * physics_object->getWidth());
    bitmap->setHeight(scale * physics_object->getHeight());
    bitmap->setX(r.x);
    bitmap->setY(r.y);
    bitmap->setRotationZ(physics_object->getAngle() + angle);
    for (auto i = object_data->collisions.begin(); i != object_data->collisions.end(); i++)
    {
        double d_i = i->impulse_change.getLength();
        if (d_i > minimum_damaging_impulse)
        {
            health -= collision_damage_koef * (d_i - minimum_damaging_impulse);
        }
        QString source_type = i->source->getType();
        if (source_type == PhysicsObject::BULLET)
        {
            health -= bullet_damage_koef;
        }
        else if (source_type == PhysicsObject::EXPLOSION)
        {
            health -= explosion_damage_koef;
        }
    }
    if (health < 0)
    {
        physics_object->invalidate();
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

>>>>>>> origin/physicsDebug

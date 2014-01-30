#include "gamemodelobject.h"
#include "console.h"

static const double collision_damage_koef = 0;
static const double bullet_damage_koef = 20;
static const double explosion_damage_koef = 20;
static const double minimum_damaging_impulse = 200;

GameModelObject::~GameModelObject()
{
    for (auto i = inner_objects.begin(); i != inner_objects.end(); i++)
    {
        delete *i;
    }
}

GameModelObject::GameModelObject(ObjectData *object_data)
{
    this->object_data = object_data;
    PhysicsObject* object = object_data->object;
    primary_type = object->getType();
    if (primary_type == PhysicsObject::VEHICLE)
    {
        Vehicle* vehicle = dynamic_cast<Vehicle*>(object);
        secondary_type = vehicle->getVehicleType();
        health = 1000;
        std::vector<Turret*> turrets = vehicle->getTurrets();
        for (auto j = turrets.begin(); j != turrets.end(); j++)
        {
            inner_objects.push_back(new GameModelObject(new ObjectData(*j)));
        }
    }
    else if (primary_type == PhysicsObject::BULLET)
    {
        secondary_type = dynamic_cast<Bullet*>(object)->getBulletType();
        health = 1000;
    }
    else if (primary_type == PhysicsObject::EXPLOSION)
    {
        secondary_type = dynamic_cast<Explosion*>(object)->getExplosionType();
        health = 1000;
    }
    else if (primary_type == PhysicsObject::TURRET)
    {
        secondary_type = dynamic_cast<Turret*>(object)->getTurretType();
        health = 1000;
    }
    else if (primary_type == PhysicsObject::OBSTACLE)
    {
        secondary_type = dynamic_cast<Obstacle*>(object)->getObstacleType();
        if (secondary_type == Obstacle::STONE_WALL)
        {
            health = 1e100;
        }
        else if (secondary_type == Obstacle::WOODEN_BARREL)
        {
            health = 300;
        }
        else if (secondary_type == Obstacle::WOODEN_BOX)
        {
            health = 100;
        }
    }
    PhysicsObject* physics_object = object_data->object;
    this->r = physics_object->getCoordinates();
    this->v = physics_object->getSpeed();
    this->angle = physics_object->getAngle();
    this->angular_speed = physics_object->getAngularSpeed();
    this->width = physics_object->getImageWidth();
    this->height = physics_object->getImageHeight();
    this->id = physics_object->getId();
}

GameModelObject::GameModelObject(int id, Vector2D r, Vector2D v,
                                 double angle, double angular_speed,
                                 int primary_type, int secondary_type,
                                 double health, double width, double height,
                                 std::vector<GameModelObject *> inner_objects)
    : id(id), r(r), v(v), angle(angle), angular_speed(angular_speed),
      primary_type(primary_type), secondary_type(secondary_type), health(health),
      inner_objects(inner_objects), width(width), height(height)
{
    this->object_data = 0;
}

std::vector<GameModelObject*> GameModelObject::getInnerObjects()
{
    return this->inner_objects;
}

void GameModelObject::update(double dt, Vector2D parent_r, double parent_angle)
{
    if (object_data != 0)
    {
        PhysicsObject* physics_object = object_data->object;
        int num = object_data->collisions.size();
        if (num > 0)
        {
            Collision* ptr = &object_data->collisions.front();
            for (int i = 0; i < num; i++)
            {
                double d_i = ptr[i].impulse_change.getLength();
                if (d_i > minimum_damaging_impulse)
                {
                    health -= collision_damage_koef * d_i;
                }
                int source_type = ptr[i].source->getType();
                if (source_type == PhysicsObject::BULLET)
                {
                    health -= bullet_damage_koef;
                }
                else if (source_type == PhysicsObject::EXPLOSION)
                {
                    health -= explosion_damage_koef;
                }
            }
        }
        if (health <= 0)
        {
            invalidate();
        }
        this->r = physics_object->getCoordinates();
        this->v = physics_object->getSpeed();
        this->angle = physics_object->getAngle();
        this->angular_speed = physics_object->getAngularSpeed();
        this->width = physics_object->getImageWidth();
        this->height = physics_object->getImageHeight();
        this->id = physics_object->getId();
    }
    else
    {
        Vector2D dr = v;
        dr.mul(dt);
        r.add(dr);
        angle += angular_speed * dt;
    }
    global_r = r;
    global_r.rotate(parent_angle);
    global_r.add(parent_r);
    global_angle = angle + parent_angle;
    int num = inner_objects.size();
    if (num > 0)
    {
        GameModelObject** ptr = &inner_objects.front();
        for (int i = 0; i < num; i++)
        {
            ptr[i]->update(dt, global_r, global_angle);
        }
    }
}

void GameModelObject::invalidate()
{
    this->object_data->object->invalidate();
    int num = inner_objects.size();
    if (num > 0)
    {
        GameModelObject** ptr = &inner_objects.front();
        for (int i = 0; i < num; i++)
        {
            ptr[i]->invalidate();
        }
    }
}

bool GameModelObject::isValid()
{
    return (this->object_data == 0) || (this->object_data->object->isValid());
}

int GameModelObject::getId()
{
    return this->id;
}

Vector2D GameModelObject::getCenter()
{
    return this->global_r;
}

double GameModelObject::getAngle()
{
    return this->global_angle;
}

double GameModelObject::getWidth()
{
    return this->width;
}

double GameModelObject::getHeight()
{
    return this->height;
}

int GameModelObject::getPrimaryType()
{
    return this->primary_type;
}

int GameModelObject::getSecondaryType()
{
    return this->secondary_type;
}

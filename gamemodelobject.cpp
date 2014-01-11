#include "gamemodelobject.h"

static const double collision_damage_koef = 2e-3;
static const double bullet_damage_koef = 0.2;
static const double explosion_damage_koef = 1;
static const double minimum_damaging_impulse = 100;

GameModelObject::GameModelObject(ObjectData *object_data)
{
    this->object_data = object_data;
    PhysicsObject* object = object_data->object;
    primaryType = object->getType();
    if (primaryType == PhysicsObject::VEHICLE)
    {
        Vehicle* vehicle = dynamic_cast<Vehicle*>(object);
        secondaryType = vehicle->getVehicleType();
        health = 1000;
        std::vector<Turret*> turrets = vehicle->getTurrets();
        for (auto j = turrets.begin(); j != turrets.end(); j++)
        {
            inner_objects.push_back(new GameModelObject(new ObjectData(*j)));
        }
    }
    else if (primaryType == PhysicsObject::BULLET)
    {
        secondaryType = dynamic_cast<Bullet*>(object)->getBulletType();
        health = 1000;
    }
    else if (primaryType == PhysicsObject::EXPLOSION)
    {
        secondaryType = dynamic_cast<Explosion*>(object)->getExplosionType();
        health = 1000;
    }
    else if (primaryType == PhysicsObject::TURRET)
    {
        secondaryType = dynamic_cast<Turret*>(object)->getTurretType();
        health = 1000;
    }
    else if (primaryType == PhysicsObject::OBSTACLE)
    {
        secondaryType = dynamic_cast<Obstacle*>(object)->getObstacleType();
        if (secondaryType == Obstacle::STONE_WALL)
        {
            health = 1e100;
        }
        else if (secondaryType == Obstacle::WOODEN_BARREL)
        {
            health = 100;
        }
        else if (secondaryType == Obstacle::WOODEN_BOX)
        {
            health = 100;
        }
    }
}

std::vector<GameModelObject*> GameModelObject::getInnerObjects()
{
    return this->inner_objects;
}

void GameModelObject::update()
{
    PhysicsObject* physics_object = object_data->object;
    for (auto i = object_data->collisions.begin(); i != object_data->collisions.end(); i++)
    {
        double d_i = i->impulse_change.getLength();
        if (d_i > minimum_damaging_impulse)
        {
            health -= collision_damage_koef * d_i;
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
        (*i)->update();
    }
}

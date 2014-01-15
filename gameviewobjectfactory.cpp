#include "gameviewobjectfactory.h"
#include "console.h"

GameViewObjectFactory::GameViewObjectFactory()
{
}

GameViewObject* GameViewObjectFactory::createGameViewObject(GameModelObject *game_model_object)
{
    std::vector<GameViewObject*> inner_objects;
    std::vector<GameModelObject*> model_inner_objects = game_model_object->getInnerObjects();
    for (auto i = model_inner_objects.begin(); i != model_inner_objects.end(); i++)
    {
        inner_objects.push_back(GameViewObjectFactory::createGameViewObject(*i));
    }
    QString path;
    QString primary_type = game_model_object->getPrimaryType();
    QString secondary_type = game_model_object->getSecondaryType();
    if (primary_type == PhysicsObject::VEHICLE)
    {
        if (secondary_type == Vehicle::DODGE_CHALLENGER_SRT8)
        {
            path = "\\DATA\\Textures\\Vehicles\\dodge_small.png";
        }
        else if (secondary_type == Vehicle::FERRARI_599GTO)
        {
            path = "\\DATA\\Textures\\Vehicles\\ferrari_small.png";
        }
    }
    else if (primary_type == PhysicsObject::BULLET)
    {
        if (secondary_type == Bullet::BULLET)
        {
            path = "\\DATA\\Textures\\Bullets\\bullet.png";
        }
        else if (secondary_type == Bullet::MISSILE)
        {
            path = "\\DATA\\Textures\\Bullets\\missile.png";
        }
        else if (secondary_type == Bullet::CUT)
        {
            path = "\\DATA\\Textures\\Bullets\\cut.png";
        }
    }
    else if (primary_type == PhysicsObject::EXPLOSION)
    {
        path = "\\DATA\\Textures\\Bullets\\explosion.png";
    }
    else if (primary_type == PhysicsObject::TURRET)
    {
        if (secondary_type == Turret::MACHINEGUN)
        {
            path = "\\DATA\\Textures\\Turrets\\machinegun.png";
        }
        else if (secondary_type == Turret::ROCKET_LAUNCHER)
        {
            path = "\\DATA\\Textures\\Turrets\\rocket_launcher.png";
        }
        else if (secondary_type == Turret::SAW)
        {
            path = "\\DATA\\Textures\\Turrets\\saw.png";
        }
    }
    else if (primary_type == PhysicsObject::OBSTACLE)
    {
        if (secondary_type == Obstacle::STONE_WALL)
        {
            path = "\\DATA\\Textures\\Obstacles\\stone_wall.png";
        }
        else if (secondary_type == Obstacle::WOODEN_BARREL)
        {
            path = "\\DATA\\Textures\\Obstacles\\wooden_barrel.png";
        }
        else if (secondary_type == Obstacle::WOODEN_BOX)
        {
            path = "\\DATA\\Textures\\Obstacles\\wooden_box.png";
        }
    }
    //Console::print(path);
    return new GameViewObject(path, inner_objects, game_model_object);
}

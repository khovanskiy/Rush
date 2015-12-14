#ifndef GAMEPLAYSTATE_H
#define GAMEPLAYSTATE_H

#include "../common/state.h"

#include "networkserver.h"
#include "mouse.h"
#include "mouseevent.h"
#include "uivehiclecontroller.h"
#include "cameracontroller.h"
#include "mapview.h"
#include "camera.h"

#define WAIT_VEHICLE 1
#define NEED_INIT_VEHICLE 2
#define INITED 3

//static const double M_PI = 3.14159265358979323846;

struct WorkView : public Sprite
{
public:
    WorkView(int id_object, GameObjectType class_object, int type_object)
    {
        this->image = 0;
        this->id_object = id_object;
        this->class_object = class_object;
        if (class_object == GameObjectType::VEHICLE)
        {
            image = new Bitmap();
            switch (type_object)
            {
            case 0:
            {
                image->load("DATA/Textures/Vehicles/dodge.png");
                image->setWidth(1.923);
                image->setHeight(5.0);
            } break;
            case 1:
            {
                image->load("DATA/Textures/Vehicles/ferrari.png");
                image->setWidth(1.962);
                image->setHeight(4.710);
            } break;
            case 2:
            {
                image->load("DATA/Textures/Vehicles/ford-f-150.png");
                image->setWidth(100 * 0.0254);
                image->setHeight(232.1 * 0.0254);
            } break;
            }
            image->setRSPointCenter();
        }
        else if (class_object == GameObjectType::TURRET)
        {
            image = new Bitmap();
            image->load("DATA/Textures/Turrets/nailgun.png");
            image->setWidth(1.5);
            image->setHeight(1.5);
            image->setRSPointCenter();
        }
        else if (class_object == GameObjectType::OBSTACLE)
        {
            switch(type_object)
            {
            case 0:
            {
                image = new Bitmap();
                image->load("DATA/Textures/Obstacles/wall_texture.png");
                image->setWidth(200);
                image->setHeight(10);
                image->setRSPointCenter();
            } break;
            case 1:
            {
                image = new Bitmap();
                image->load("DATA/Textures/Obstacles/wooden_box.png");
                image->setWidth(1);
                image->setHeight(1);
                image->setRSPointCenter();
            } break;
            case 2:
            {
                image = new Bitmap();
                image->load("DATA/Textures/Obstacles/wooden_barrel.png");
                image->setWidth(2);
                image->setHeight(2);
                image->setRSPointCenter();
            } break;
            case 3:
            {
                image = new Bitmap();
                image->load("DATA/Textures/Obstacles/wooden_barrel.png");
                image->setWidth(4);
                image->setHeight(4);
                image->setRSPointCenter();
            } break;
            }
        }
        else if (class_object == GameObjectType::TERRAIN)
        {
            image = new Bitmap();
            image->load("DATA/Textures/Terrains/3.jpg");
            image->setWidth(100);
            image->setHeight(100);
        }
        else if (class_object == GameObjectType::BULLET)
        {
            image = new Bitmap();
            switch (type_object)
            {
            case 0:
            {
                image->load("DATA/Textures/Bullets/bullet.png");
                image->setWidth(0.1);
                image->setHeight(0.43);
            } break;
            case 1:
            {
                image->load("DATA/Textures/Bullets/missile.png");
                image->setWidth(0.5);
                image->setHeight(1.9);
            } break;
            case 2:
            {
                image->load("DATA/Textures/Bullets/plazma.png");
                image->setWidth(1);
                image->setHeight(1);
            } break;
            }
            image->setRSPointCenter();
        }
        if (image)
        {
            //image->setInter(true);
            this->setX(1e6);
            this->setY(1e6);
            this->setInter(true);
            addChild(image);
            valid = true;
            acc_state = AccelerationState::NoAcc;
            rotation_percent = 0;
            firing_state = false;
        }
        cache_work[id_object] = this;
    }

    void render(QPainter * painter, const Matrix &base, bool new_tick, float interpolation)
    {
        Sprite::render(painter, base, new_tick, interpolation);
        if (class_object == VEHICLE)
        {
            Console::print(QString("") + QVariant(position.x).toString()
                           + QString(",") + QVariant(position.y).toString());
        }
    }

    ~WorkView()
    {
        if (image)
        {
            delete image;
        }
        cache_work.erase(id_object);
    }
    static WorkView* findById(int id)
    {
        std::map<int, WorkView*>::iterator i = cache_work.find(id);
        if (i != cache_work.end())
        {
            return (*i).second;
        }
        else
        {
            return 0;
        }
    }

    int id_object;
    GameObjectType class_object;
    Bitmap* image;
    bool valid;
    AccelerationState acc_state;
    double rotation_percent;
    bool firing_state;
    static std::map<int, WorkView*> cache_work;
};

struct UIController : public EventHandler
{
public:
    UIController(WorkView* vehicle)
    {
        this->vehicle = vehicle;
        Keyboard::gi()->addEventListener(this);
        Mouse::gi()->addEventListener(this);
    }

    ~UIController()
    {
        Mouse::gi()->removeEventListener(this);
        Keyboard::gi()->removeEventListener(this);
    }

    void Invoke(const Event &event)
    {
        if (!vehicle)
        {
            return;
        }
        if (event.type == MouseEvent::MOUSE_DOWN)
        {
            vehicle->firing_state = true;
        }
        else if (event.type == MouseEvent::MOUSE_UP)
        {
            vehicle->firing_state = false;
        }
        else if (event.type == KeyboardEvent::KEY_DOWN)
        {
            const KeyboardEvent* e = static_cast<const KeyboardEvent*>(&event);
            switch (e->keyCode)
            {
                case Qt::Key_W:
                {
                    vehicle->acc_state = ForwardAcc;
                } break;
                case Qt::Key_S:
                {
                    vehicle->acc_state = BackwardAcc;
                } break;
                case Qt::Key_A:
                {
                    vehicle->rotation_percent = -1;
                } break;
                case Qt::Key_D:
                {
                    vehicle->rotation_percent = 1;
                } break;
                case Qt::Key_Space:
                {
                    vehicle->acc_state = Brakes;
                } break;
            }
        }
        else if (event.type == KeyboardEvent::KEY_UP)
        {
            const KeyboardEvent* st = static_cast<const KeyboardEvent*>(&event);
            switch (st->keyCode)
            {
                case Qt::Key_W:
                {
                        vehicle->acc_state = NoAcc;
                } break;
                case Qt::Key_S:
                {
                        vehicle->acc_state = NoAcc;
                } break;
                case Qt::Key_A:
                {
                        vehicle->rotation_percent = 0;
                } break;
                case Qt::Key_D:
                {
                        vehicle->rotation_percent = 0;
                } break;
                case Qt::Key_Space:
                {
                        vehicle->acc_state = NoAcc;
                } break;
            }
        }
    }
    WorkView* vehicle;
};


struct ArrowsView : public Sprite
{
public:

    ArrowsView(std::vector<WorkView*>* list)
    {
        arrow = new Bitmap();
        arrow->load("DATA/Textures/gui/enemy-arrow.png");
        arrow->setSize(Vector2D(20,20));
        this->list = list;
    }

    void render(QPainter *render2d, const Matrix &base, bool new_tick, float interpolation)
    {
        Matrix camera_matrix = Camera::gi()->getTransform();
        Camera* camera = Camera::gi();
        for (int i = 0; i < list->size(); ++i)
        {
            if (list->at(i)->class_object != GameObjectType::VEHICLE)
            {
                continue;
            }
            WorkView* view = list->at(i);
            Vector2D view_pos = camera_matrix.map(view->getPosition());
            bool hit = view_pos.x >= 0 &&  view_pos.x <= Camera::gi()->screen_width && view_pos.y >=0 && view_pos.y <= Camera::gi()->screen_height;
            if (!hit)
            {
                view_pos.x -= camera->screen_width / 2;
                view_pos.y -= camera->screen_height / 2;
                double angle = atan2(view_pos.y, view_pos.x) - M_PI / 2;
                Vector2D r(0,1);
                r.mul(100);
                r.rotate(angle);
                r.x += camera->screen_width / 2;
                r.y += camera->screen_height / 2;
                arrow->setRotationZ(angle);
                arrow->render(render2d, Matrix::translation(r), new_tick, interpolation);
            }
        }
    }

    ~ArrowsView()
    {
        delete arrow;
    }

    Bitmap* arrow;
    std::vector<WorkView*>* list;
};

struct Player
{
    int id_player;
    int count_kills;
    int count_dieds;
    int health;
    double speed;
    double spins;
    Player()
    {
        id_player = 0;
        count_kills = 0;
        count_dieds = 0;
        health = 0;
        speed = 0;
        spins = 0;
    }
};

struct StatView : public Sprite
{
public:
    StatView(std::map<int, Player*>* map)
    {
        this->map = map;
        me = QColor::fromRgb(0xff, 0xcc, 0x0, 0xff);
        enemy = QColor::fromRgbF(1,1,1,1);
        pen = QPen(enemy);
        font = QFont("Arial", 15);
        current_player_id = 0;
    }


    void render(QPainter *render2d, const Matrix &base, bool new_tick, float interpolation)
    {
        render2d->setFont(font);
        int k = 0;
        for (std::map<int, Player*>::iterator i = map->begin(); i != map->end(); ++i)
        {
            Player* player = (*i).second;
            if (current_player_id == player->id_player)
            {
                pen.setColor(me);
            }
            else
            {
                pen.setColor(enemy);
            }
            render2d->setPen(pen);
            QString text = QString("Player #") + QVariant(player->id_player).toString() + ": " + QVariant(player->count_kills).toString() + "-" + QVariant(player->count_dieds).toString();
            render2d->drawText(10, 30 + k * 30, text);
            ++k;
        }
    }

    int current_player_id;

    QColor enemy;
    QColor me;
    QFont font;
    QPen pen;
    std::map<int, Player*>* map;
};

struct SpeedometerView : public Sprite
{
public:
    SpeedometerView(std::map<int, Player*>* map)
    {
        this->map = map;
        arrow = new Bitmap();
        arrow->load("DATA/Textures/gui/speedo-arrow.png");
        speedo = new Bitmap();
        speedo->load("DATA/Textures/gui/speedo.png");
        speedo->setRSPointCenter();
        arrow->setRSPoint(Vector2D(0.5, 0.9));
    }

    void render(QPainter *render2d, const Matrix &base, bool new_tick, float interpolation)
    {
        std::map<int, Player*>::iterator i = map->find(current_player_id);
        if (i != map->end())
        {
            Player* player = (*i).second;
            Camera* camera = Camera::gi();
            render2d->setFont(QFont("Arial", 15));
            render2d->setPen(QColor::fromRgb(0xff, 0xcc, 0x0, 0xff));

            render2d->drawText(camera->screen_width - 150, camera->screen_height - 50, 100, 30, Qt::AlignRight, QVariant(player->health).toString() + "%");

            speedo->setX(100);
            speedo->setY(camera->screen_height - 100);
            speedo->render(render2d, base, new_tick, interpolation);

            arrow->setX(100);
            arrow->setY(camera->screen_height - 100);
            arrow->setRotationZ(3 * M_PI / 2 * (player->speed * 3.6 / 220) - 3 * M_PI / 4);
            arrow->render(render2d, base, new_tick, interpolation);

            //render2d->drawText(10, camera->screen_height - 50, QVariant(player->spins).toString());
            render2d->setPen(QColor::fromRgb(0x0, 0x0, 0x0, 0xff));
            render2d->drawText(70, camera->screen_height - 65, 70, 20, Qt::AlignCenter, QVariant(floor(player->speed * 3.6)).toString());
        }
    }

    Bitmap* arrow;
    Bitmap* speedo;
    int current_player_id;
    std::map<int, Player*>* map;
};

class GameplayState : public State, public EventHandler
{
public:
    void init();
    void render(const RenderData &);
    void tick(double dt);
    void Invoke(const Event &);
    void release();
private:
    int current_id_player;
    int current_id_vehicle;
    int current_state;
    WorkView* current_vehicle;
    UIController* controls;

    NetworkServer* server;
    ArrowsView* arrows_view;
    StatView* stat_view;
    SpeedometerView* speedometer_view;

    std::vector<WorkView*> view_list;
    std::vector<WorkView*> unused_view_list;
    std::map<int, Player*> players;
};

#endif // GAMEPLAYSTATE_H

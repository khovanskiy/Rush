#ifndef GAMEPLAYSTATE_H
#define GAMEPLAYSTATE_H

#include "state.h"

#include "bitmap.h"
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

static const double M_PI = 3.14159265358979323846;

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
                image->load("DATA\\Textures\\Vehicles\\dodge.png");
                image->setWidth(1.923);
                image->setHeight(5.0);
            } break;
            case 1:
            {
                image->load("DATA\\Textures\\Vehicles\\ferrari.png");
                image->setWidth(1.962);
                image->setHeight(4.710);
            } break;
            case 2:
            {
                image->load("DATA\\Textures\\Vehicles\\ford-f-150.png");
                image->setWidth(100 * 0.0254);
                image->setHeight(232.1 * 0.0254);
            } break;
            }
            image->setRSPointCenter();
        }
        else if (class_object == GameObjectType::TURRET)
        {
            image = new Bitmap();
            image->load("DATA\\Textures\\Turrets\\nailgun.png");
            image->setWidth(1.5);
            image->setHeight(1.5);
            image->setRSPointCenter();
        }
        else if (class_object == GameObjectType::OBSTACLE)
        {
            image = new Bitmap();
            image->load("DATA\\Textures\\Obstacles\\stone_wall.png");
            image->setWidth(20);
            image->setHeight(2);
            image->setRSPointCenter();
        }
        else if (class_object == GameObjectType::TERRAIN)
        {
            image = new Bitmap();
            image->load("DATA\\Textures\\Terrains\\1.jpg");
            image->setWidth(200);
            image->setHeight(200);
        }
        else if (class_object == GameObjectType::BULLET)
        {
            image = new Bitmap();
            image->load("DATA\\Textures\\Bullets\\bullet.png");
            image->setWidth(0.1);
            image->setHeight(0.43);
            image->setRSPointCenter();
        }
        if (image)
        {
            image->setInter(true);
            this->setInter(true);
            Console::print("add image");
            addChild(image);
            valid = true;
            acc_state = AccelerationState::NoAcc;
            rotation_percent = 0;
            firing_state = false;
        }
        cache_work[id_object] = this;
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
        arrow->load("DATA\\Textures\\bonus.png");
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

    std::vector<WorkView*> view_list;
    std::vector<WorkView*> unused_view_list;
};

#endif // GAMEPLAYSTATE_H

#include "uivehiclecontroller.h"

UIVehicleController::UIVehicleController(Vehicle* vehicle)
{
    this->vehicle = vehicle;
    vehicle->addEventListener(this);
    Keyboard::gi()->addEventListener(this);
    Mouse::gi()->addEventListener(this);
}

UIVehicleController::~UIVehicleController()
{
    vehicle->removeEventListener(this);
    Mouse::gi()->removeEventListener(this);
}

void UIVehicleController::Invoke(const Event &event)
{
    if (event.type == MouseEvent::MOUSE_MOVE)
    {
        const MouseEvent* e = static_cast<const MouseEvent*>(&event);
        vehicle->turretsToPoint(Vector2D(e->getX() / 35.0, e->getY() / 35.0));
    }
    else if (event.type == Event::INVALIDATE)
    {
        vehicle->removeEventListener(this);
        dispatchEvent(Event(this, Event::INVALIDATE));
    }
    else if (event.type == KeyboardEvent::KEY_DOWN)
    {
        const KeyboardEvent* e = static_cast<const KeyboardEvent*>(&event);
        switch (e->keyCode)
        {
            case Qt::Key_W:
            {
                vehicle->setAccelerationState(ForwardAcc);
            } break;
            case Qt::Key_S:
            {
                vehicle->setAccelerationState(BackwardAcc);
            } break;
            case Qt::Key_A:
            {
                vehicle->setRotationPercent(-1);
            } break;
            case Qt::Key_D:
            {
                vehicle->setRotationPercent(1);
            } break;
            case Qt::Key_Space:
            {
                vehicle->setAccelerationState(Brakes);
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
                    vehicle->setAccelerationState(NoAcc);
            } break;
            case Qt::Key_S:
            {
                    vehicle->setAccelerationState(NoAcc);
            } break;
            case Qt::Key_A:
            {
                    vehicle->setRotationPercent(0);
            } break;
            case Qt::Key_D:
            {
                    vehicle->setRotationPercent(0);
            } break;
            case Qt::Key_Space:
            {
                    vehicle->setAccelerationState(NoAcc);
            } break;
        }
    }
}

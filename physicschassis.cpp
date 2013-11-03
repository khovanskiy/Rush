#include "physicschassis.h"
typedef std::vector<PhysicsWheel*> vector;
typedef vector::iterator iterator;
#define M_PI	 3.14159265358979323846

static const double g = 9.8;

PhysicsChassis::PhysicsChassis(vector wheels, PhysicsVehicleEngine engine,
                               double weight, Vector2D mass_center, double height)
    : wheels(wheels), engine(engine), mass_center(mass_center)
{
    this->weight = weight;
    this->height = height;
}

void PhysicsChassis::distributeWeigth()
{
    Vector2D mass_center_offset;
    mass_center_offset.x = height * a.x / sqrt(a.x * a.x + g * g);
    mass_center_offset.y -= height * a.y / sqrt(a.y * a.y + g * g);
    int front_amount = 0, back_amount = 0;
    double front_sum = 0, back_sum = 0;
    for (iterator i = wheels.begin(); i != wheels.end(); i++)
    {
        if ((*i)->r.y > mass_center_offset.y)
        {
            front_amount++;
            front_sum += (*i)->r.y - mass_center_offset.y;
        }
        else
        {
            back_amount++;
            back_sum += mass_center_offset.y - (*i)->r.y;
        }
    }
    double front_weight = weight * back_sum / (front_amount * back_sum + back_amount * front_sum);
    double back_weight = weight * front_sum / (front_amount * back_sum + back_amount * front_sum);
    for (iterator i = wheels.begin(); i != wheels.end(); i++)
    {
        if ((*i)->r.y > mass_center_offset.y)
        {
            (*i)->distributed_weight = front_weight;
        }
        else
        {
            (*i)->distributed_weight = back_weight;
        }
    }
    double left_sum = 0, right_sum = 0;
    for (iterator i = wheels.begin(); i != wheels.end(); i++)
    {
        if ((*i)->r.x != 0)
        {
            if ((*i)->r.x < mass_center_offset.x)
            {
                left_sum += mass_center_offset.x - (*i)->r.x;
            }
            else
            {
                right_sum += (*i)->r.x - mass_center_offset.x;
            }
        }
    }
    double left_koef = right_sum * (left_sum + right_sum);
    double right_koef = left_sum * (left_sum + right_sum);
    for (iterator i = wheels.begin(); i != wheels.end(); i++)
    {
        if ((*i)->r.x != 0)
        {
            if ((*i)->r.x < mass_center_offset.x)
            {
                (*i)->distributed_weight *= left_koef;
            }
            else
            {
                (*i)->distributed_weight *= right_koef;
            }
        }
    }
}

void PhysicsChassis::setWheelsSpeed()
{
    for (iterator i = wheels.begin(); i != wheels.end(); i++)
    {
        Vector2D rot = (*i)->r;
        rot.rotate(M_PI / 2);
        rot.mul(angular_speed);
        (*i)->v = v;
        (*i)->v.add(rot);
    }
}

void PhysicsChassis::setWheelsReaction()
{
    for (iterator i = wheels.begin(); i != wheels.end(); i++)
    {
        (*i)->changeState(acc_state, rotation);
    }
}

void PhysicsChassis::distributeTorque()
{
    double max_rotation = 0, cur_rotation;
    double total_torque = 0;
    for (iterator i = wheels.begin(); i != wheels.end(); i++)
    {
        cur_rotation = (*i)->getRotatingSpeed();
        if (max_rotation < cur_rotation)
        {
            max_rotation = cur_rotation;
        }
        total_torque += (*i)->getMaxAccelerationTorque();
    }
    engine.setRotations(max_rotation);
    double p = engine.getTorque(torque_percent) / max_rotation;
    if (p > 1)
    {
        p = 1;
    }
    for (iterator i = wheels.begin(); i != wheels.end(); i++)
    {
        (*i)->setTorque(p);
    }
}

void PhysicsChassis::sumForces(double dt)
{
    f.x = 0;
    f.y = 0;
    force_moment = 0;
    for (iterator i = wheels.begin(); i != wheels.end(); i++)
    {
        (*i)->calculateForces(dt);
        f.add((*i)->f);
        force_moment += ((*i)->force_moment);
    }
}

void PhysicsChassis::setTotalState(Vector2D v, Vector2D a, double angular_speed,
                                   double torque_percent, AccelerationState acc_state,
                                   double rotation)
{
    this->v = v;
    this->a = a;
    this->angular_speed = angular_speed;
    this->torque_percent = torque_percent;
    this->acc_state = acc_state;
    this->rotation = rotation;
}

void PhysicsChassis::calculateForces(double dt)
{
    distributeWeigth();
    setWheelsSpeed();
    setWheelsReaction();
    distributeTorque();
    sumForces(dt);
}



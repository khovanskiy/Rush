#include "chassis.h"
//#include "console.h"

typedef std::vector<Wheel*> vector;
typedef vector::iterator iterator;
static const double G = 9.80665;
static const double M_PI = 3.14159265358979323846;
static const double eps = 1e-3;


Chassis::Chassis(vector const & wheels, VehicleEngine const & engine,
                               double weight, Vector2D const & mass_center, double height)
    : wheels(wheels), engine(engine), mass_center(mass_center)
{
    this->weight = weight;
    this->height = height;
}

Chassis::Chassis(const Chassis &chassis)
    : wheels(chassis.wheels), engine(chassis.engine), mass_center(chassis.mass_center)
{
    this->weight = chassis.weight;
    this->height = chassis.height;
}

void Chassis::distributeWeigth()
{
    Vector2D mass_center_offset;
    mass_center_offset.x = height * a.x / sqrt(a.x * a.x + G * G);
    mass_center_offset.y -= height * a.y / sqrt(a.y * a.y + G * G);
    int front_amount = 0, back_amount = 0;
    double front_sum = 0, back_sum = 0;
    //Console::print("Weight:");
    //Console::print(weight);
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
    //Console::print("Front weigth:");
    //Console::print(front_weight);
    //Console::print("Back weight");
    //Console::print(back_weight);
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
        if (abs((*i)->r.x) > eps)
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
    double left_koef = 2 * right_sum / (left_sum + right_sum);
    double right_koef = 2 * left_sum / (left_sum + right_sum);
    for (iterator i = wheels.begin(); i != wheels.end(); i++)
    {
        if (abs((*i)->r.x) > eps)
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
        //Console::print("Distributed weight:");
        //Console::print((*i)->distributed_weight);
    }
}

void Chassis::setWheelsSpeed()
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

void Chassis::setWheelsReaction()
{
    for (iterator i = wheels.begin(); i != wheels.end(); i++)
    {
        (*i)->changeState(acc_state, rotation);
    }
}

void Chassis::distributeTorque()
{
    double min_rotation = 1e10, cur_rotation;
    double total_torque = 0;
    for (iterator i = wheels.begin(); i != wheels.end(); i++)
    {
        cur_rotation = (*i)->getRotatingSpeed();
        if ((cur_rotation > eps) && (min_rotation > cur_rotation))
        {
            min_rotation = cur_rotation;
        }
        total_torque += (*i)->getMaxAccelerationTorque();
    }
    engine.setRotations(min_rotation);
    double p = engine.getTorque(torque_percent) / total_torque;
    if (p > 1)
    {
        p = 1;
    }
    for (iterator i = wheels.begin(); i != wheels.end(); i++)
    {
        (*i)->setTorque(p);
        //Console::print("Distributed torque:");
        //Console::print(p);
    }
}

void Chassis::sumForces(double dt)
{
    f.x = 0;
    f.y = 0;
    force_moment = 0;
    for (iterator i = wheels.begin(); i != wheels.end(); i++)
    {
        (*i)->calculateForces(dt);
        f.add((*i)->f);
        force_moment += ((*i)->force_moment);
        //Console::print("Force:");
        //Console::print((*i)->f);
        //Console::print("Force moment:");
        //Console::print((*i)->force_moment);
    }
    /*if (f.getLength() > (weight / G) * v.getLength() / dt)
    {
        f.setLength((weight / G) * v.getLength() / dt);
    }*/
}

void Chassis::setTotalState(Vector2D const & v, Vector2D const & a, double angular_speed,
                                   double torque_percent, AccelerationState const & acc_state,
                                   double rotation)
{
    this->v = v;
    this->a = a;
    this->angular_speed = angular_speed;
    this->torque_percent = torque_percent;
    this->acc_state = acc_state;
    this->rotation = rotation;
}

void Chassis::calculateForces(double dt)
{
    distributeWeigth();
    setWheelsSpeed();
    setWheelsReaction();
    distributeTorque();
    sumForces(dt);
    //Console::print(f);
    //Console::print(Vector2D(force_moment, 0));
}

int Chassis::getGear()
{
    return engine.getGear();
}

double Chassis::getSpins()
{
    return engine.getSpins();
}

void Chassis::deleteWheels()
{
    for (iterator i = wheels.begin(); i != wheels.end(); i++)
    {
        delete (*i);
    }
    wheels.clear();
}



#include "chassis.h"
#include "console.h"

typedef std::vector<Wheel *> vector;
typedef vector::iterator iterator;
static const double G = 9.80665;
//static const double M_PI = 3.14159265358979323846;
static const double rotation_infinity = 1e10;
static const double eps = 1e-3;
static const double height_koef = 1 / 6;


Chassis::Chassis() {
}

Chassis::Chassis(const Chassis &chassis)
        : engine(chassis.engine), mass_center(chassis.mass_center) {
    this->weight = chassis.weight;
    this->height = chassis.height;
}

Chassis::~Chassis() {
    for (iterator i = this->wheels.begin(); i != this->wheels.end(); i++) {
        delete (*i);
    }
}

void Chassis::setWheels(double mass, double height, CarTrack back, CarTrack front) {
    for (iterator i = this->wheels.begin(); i != this->wheels.end(); i++) {
        delete (*i);
    }
    wheels.clear();
    this->mass_center = Vector2D(0, back.y * back.weigth_percent + front.y * front.weigth_percent);
    this->height = height * height_koef;
    this->weight = mass * G;
    this->wheels.push_back(new CarWheel(front.mu_parallel_friction, front.mu_parallel_roll,
                                        front.mu_perpendicular_friction, front.mu_broken_friction,
                                        front.max_angle, Vector2D(-front.width / 2, front.y - mass_center.y),
                                        front.wheel_radius, front.driving, front.braking, front.reaction));
    this->wheels.push_back(new CarWheel(front.mu_parallel_friction, front.mu_parallel_roll,
                                        front.mu_perpendicular_friction, front.mu_broken_friction,
                                        front.max_angle, Vector2D(front.width / 2, front.y - mass_center.y),
                                        front.wheel_radius, front.driving, front.braking, front.reaction));
    this->wheels.push_back(new CarWheel(back.mu_parallel_friction, back.mu_parallel_roll,
                                        back.mu_perpendicular_friction, back.mu_broken_friction,
                                        back.max_angle, Vector2D(-back.width / 2, back.y - mass_center.y),
                                        back.wheel_radius, back.driving, back.braking, back.reaction));
    this->wheels.push_back(new CarWheel(back.mu_parallel_friction, back.mu_parallel_roll,
                                        back.mu_perpendicular_friction, back.mu_broken_friction,
                                        back.max_angle, Vector2D(back.width / 2, back.y - mass_center.y),
                                        back.wheel_radius, back.driving, back.braking, back.reaction));
}

void Chassis::setEngine(VehicleEngine const &engine) {
    this->engine = engine;
}

void Chassis::setStructure(double mass, const Vector2D &mass_center, double height) {
    this->weight = mass * G;
    this->mass_center = mass_center;
    this->height = height * height_koef;
}

void Chassis::distributeWeigth() {
    Vector2D mass_center_offset;
    mass_center_offset.x = height * a.x / sqrt(a.x * a.x + G * G);
    mass_center_offset.y -= height * a.y / sqrt(a.y * a.y + G * G);
    int front_amount = 0, back_amount = 0;
    double front_sum = 0, back_sum = 0;
    for (iterator i = wheels.begin(); i != wheels.end(); i++) {
        if ((*i)->r.y > mass_center_offset.y) {
            front_amount++;
            front_sum += (*i)->r.y - mass_center_offset.y;
        }
        else {
            back_amount++;
            back_sum += mass_center_offset.y - (*i)->r.y;
        }
    }
    double front_weight = weight * back_sum / (front_amount * back_sum + back_amount * front_sum);
    double back_weight = weight * front_sum / (front_amount * back_sum + back_amount * front_sum);
    for (iterator i = wheels.begin(); i != wheels.end(); i++) {
        if ((*i)->r.y > mass_center_offset.y) {
            (*i)->distributed_weight = front_weight;
        }
        else {
            (*i)->distributed_weight = back_weight;
        }
    }
    double left_sum = 0, right_sum = 0;
    for (iterator i = wheels.begin(); i != wheels.end(); i++) {
        if (std::abs((*i)->r.x) > eps) {
            if ((*i)->r.x < mass_center_offset.x) {
                left_sum += mass_center_offset.x - (*i)->r.x;
            }
            else {
                right_sum += (*i)->r.x - mass_center_offset.x;
            }
        }
    }
    double left_koef = 2 * right_sum / (left_sum + right_sum);
    double right_koef = 2 * left_sum / (left_sum + right_sum);
    for (iterator i = wheels.begin(); i != wheels.end(); i++) {
        if (std::abs((*i)->r.x) > eps) {
            if ((*i)->r.x < mass_center_offset.x) {
                (*i)->distributed_weight *= left_koef;
            }
            else {
                (*i)->distributed_weight *= right_koef;
            }
            //Console::print("Distributed weight:");
            //Console::print((*i)->distributed_weight);
        }
    }
}

void Chassis::setWheelsSpeed() {
    for (iterator i = wheels.begin(); i != wheels.end(); i++) {
        Vector2D rot = (*i)->r;
        rot.rotate(M_PI / 2);
        rot.mul(angular_speed);
        (*i)->v = v;
        (*i)->v.add(rot);
    }
}

void Chassis::setWheelsReaction() {
    for (iterator i = wheels.begin(); i != wheels.end(); i++) {
        (*i)->changeState(acc_state, rotation);
    }
}

void Chassis::distributeTorque() {
    double min_rotation = rotation_infinity, cur_rotation;
    double total_torque = 0;
    for (iterator i = wheels.begin(); i != wheels.end(); i++) {
        cur_rotation = (*i)->getRotatingSpeed();
        if ((cur_rotation >= 0) && (min_rotation > cur_rotation)) {
            min_rotation = cur_rotation;
        }
        //Console::print("Max acceleration torque:");
        //Console::print((*i)->getMaxAccelerationTorque());
        total_torque += (*i)->getMaxAccelerationTorque();
    }
    engine.setRotations(min_rotation);
    double p = 0;
    if (total_torque != 0) {
        p = engine.getTorque(torque_percent) / total_torque;
    }
    if (p > 1) {
        p = 1;
    }
    for (iterator i = wheels.begin(); i != wheels.end(); i++) {
        (*i)->setTorque(p);
    }
}

void Chassis::sumForces(double dt) {
    f.mul(0);
    force_moment = 0;
    for (iterator i = wheels.begin(); i != wheels.end(); i++) {
        (*i)->calculateForces(dt);
        //Console::print("Wheel force:");
        //Console::print((*i)->f);
        f.add((*i)->f);
        force_moment += ((*i)->force_moment);
    }
}

void Chassis::setTotalState(Vector2D const &v, Vector2D const &a, double angular_speed,
                            double torque_percent, AccelerationState const &acc_state,
                            double rotation) {
    this->v = v;
    this->a = a;
    this->angular_speed = angular_speed;
    this->torque_percent = torque_percent;
    this->acc_state = acc_state;
    this->rotation = rotation;
}

void Chassis::calculateForces(double dt) {
    if (wheels.size() > 0) {
        distributeWeigth();
        setWheelsSpeed();
        setWheelsReaction();
        distributeTorque();
    }
    sumForces(dt);
}

int Chassis::getGear() {
    return engine.getGear();
}

double Chassis::getSpins() {
    return engine.getSpins();
}

Vector2D Chassis::getMassCenter() {
    return this->mass_center;
}



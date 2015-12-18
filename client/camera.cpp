#include "camera.h"

Camera *Camera::instance = 0;

Camera::Camera() {
    inner_size.x = 1200;
    inner_size.y = 800;
    setRSPoint(Vector2D(0.5, 0.5));
    scaling.x = scaling.y = 15;
}

void Camera::resize(int width, int height) {
    screen_width = inner_size.x = width;
    screen_height = inner_size.y = height;
}

Camera *Camera::gi() {
    if (instance == 0) {
        instance = new Camera();
    }
    return instance;
}

Matrix &Camera::getTransform() {
    Vector2D origin(rs_point.x * inner_size.x, rs_point.y * inner_size.y);
    Matrix a = Matrix::translation(Vector2D(-position.x, -position.y));
    Matrix b = Matrix::rotationZ(rotationZ);
    Matrix c = Matrix::scaling(scaling);
    Matrix d = Matrix::translation(Vector2D(origin.x, origin.y));
    a.mul(b);
    a.mul(c);
    a.mul(d);
    /*Matrix a = Matrix::translation(Vector2D(-position.x, -position.y));
    Matrix b = Matrix::rotationZ(rotationZ);
    Matrix c = Matrix::scaling(scaling);
    Matrix d = Matrix::translation(Vector2D(rs_point.x * inner_size.x, rs_point.y * inner_size.y));
    a.mul(b);
    a.mul(c);
    a.mul(d);*/

    //Console::print("Camera");
    //Console::print(a);
    matrix = a;
    return matrix;//TransformableObject::getTransform();
}

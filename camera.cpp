#include "camera.h"

Camera* Camera::instance = 0;

Camera::Camera()
{
    width = 800;
    height = 600;
    matrix = new QMatrix();
}

void Camera::resize(int width, int height)
{
    this->width = width;
    this->height = height;
}

QMatrix* Camera::getMatrix()
{
    return matrix;
}

Camera* Camera::gi()
{
    if (instance == 0)
    {
        instance = new Camera();
    }
    return instance;
}

#include "camera.h"

Camera* Camera::instance = 0;

Camera::Camera()
{
    width = 800;
    height = 600;
    matrix = new QMatrix();
}

QMatrix* Camera::getMatrix()
{
    return matrix;
}

Camera* Camera::getInstance()
{
    if (instance == 0)
    {
        instance = new Camera();
    }
    return instance;
}

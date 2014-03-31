#include "camera.h"

Camera* Camera::instance = 0;

Camera::Camera()
{
    inner_size.x = 800;
    inner_size.y = 600;
}

void Camera::resize(int width, int height)
{
    inner_size.x = width;
    inner_size.y = height;
}

Camera* Camera::gi()
{
    if (instance == 0)
    {
        instance = new Camera();
    }
    return instance;
}

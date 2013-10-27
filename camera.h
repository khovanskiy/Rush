#ifndef CAMERA_H
#define CAMERA_H

#include <QMatrix>

class Camera
{
public:
    static Camera* gi();
    int width;
    int height;
    QMatrix* getMatrix();
    void resize(int width, int height);
private:
    Camera();
    QMatrix* matrix;
    static Camera* instance;
};

#endif // CAMERA_H

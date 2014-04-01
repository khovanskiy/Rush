#ifndef CAMERA_H
#define CAMERA_H

#include "transformableobject.h"
#include "matrix.h"

class Camera : public TransformableObject
{
public:
    static Camera* gi();
    void resize(int width, int height);
    Matrix& getTransform();
private:
    Camera();
    static Camera* instance;
};

#endif // CAMERA_H

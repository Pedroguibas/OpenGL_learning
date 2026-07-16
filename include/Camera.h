#pragma once

#include "mat.h"

class Camera {
  public:
    Vec3 position;

    float yaw;
    float pitch;

    Vec3 forward;
    Vec3 right;
    Vec3 up;

    Camera();
    Camera(Vec3 position);
    Camera(Vec3 position, float yaw, float pitch);

    void updateVectors();
    Mat4 getViewMatrix();
};
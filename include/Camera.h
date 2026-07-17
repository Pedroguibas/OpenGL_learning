#pragma once

#include "mat.h"

class Camera {
  private:
    void setDirection(const Vec3 &dir);
  public:
    Vec3 position;

    float yaw;
    float pitch;

    Vec3 forward;
    Vec3 right;
    Vec3 up;

    float fov = 60.0f;
    float nearPlane = 0.1;
    float farPlane = 100;

    Camera();
    Camera(Vec3 position);
    Camera(Vec3 position, float yaw, float pitch);

    void updateVectors();
    Mat4 getViewMatrix() const;
    void lookAt(const Vec3 &target);

    Mat4 getProjectionMatrix(int width, int height);
};
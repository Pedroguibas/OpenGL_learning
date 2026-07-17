#include "Camera.h"

#include <cmath>
using std::cos;
using std::sin;

Camera::Camera() : position(Vec3(0, 0, 0)), yaw(0), pitch(0) {}
Camera::Camera(Vec3 position) : position(position), yaw(0), pitch(0) {}
Camera::Camera(Vec3 position, float yaw, float pitch) : position(position), yaw(yaw), pitch(pitch) {}


void Camera::updateVectors() {
  this->forward.x = cos(yaw) * cos(pitch);
  this->forward.y = sin(pitch);
  this->forward.z = sin(yaw) * cos(pitch);

  this->right = normalize(cross(this->forward, Vec3(0, 1, 0)));

  this-> up = cross(right, forward);
}

Mat4 Camera::getViewMatrix() const {
  float m[4][4] = {
    {right.x, right.y, right.z, -dot(right, position)},
    {up.x, up.y, up.z, -dot(up, position)},
    {-forward.x, -forward.y, -forward.z, -dot(-forward, position)},
    {0, 0, 0, 1}
  };

  return Mat4(m);
}

void Camera::setDirection(const Vec3 &dir) {
  yaw = atan2(dir.z, dir.x);
  pitch = atan2(dir.y, sqrt(dir.x*dir.x + dir.z*dir.z));
}


void Camera::lookAt(const Vec3 &target) {
  Vec3 dir = normalize(target - position);

  setDirection(dir);

  this->updateVectors();
}


Mat4 Camera::getProjectionMatrix(int width, int height) {
  const float f = 1.0f / tan(degToRad(fov)/2);
  const float aspect = (float)width / (float)height;

  float m[4][4] = {
    {f/aspect, 0, 0, 0},
    {0, f, 0, 0},
    {0, 0, (farPlane + nearPlane) / (nearPlane - farPlane), (2.0f * farPlane * nearPlane) / (nearPlane - farPlane)},
    {0, 0, -1, 0}
  };

  return Mat4(m);
}
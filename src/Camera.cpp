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
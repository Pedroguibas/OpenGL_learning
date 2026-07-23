#include "PointLight.h"
using std::to_string;

PointLight::PointLight(Vec3 position) 
: position(position) {}

PointLight::PointLight(Vec3 position, Vec3 color) 
: position(position), color(color) {}

PointLight::PointLight(Vec3 position, Vec3 color, float constant, float linear, float quadratic) 
: position(position), color(color), constant(constant), linear(linear), quadratic(quadratic) {}

void PointLight::upload(Shader &s, int index) const {
  const string base = "lights[" + to_string(index) + "].";

  s.setVec3(base + "position", position);
  s.setVec3(base + "color", color);
  s.setFloat(base + "constant", constant);
  s.setFloat(base + "linear", linear);
  s.setFloat(base + "quadratic", quadratic);
}
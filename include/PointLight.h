#pragma once

#include "mat.h"
#include "Shader.h"

class PointLight {
  public:
    Vec3 position;
    Vec3 color = Vec3(1.0f, 1.0f, 1.0f);

    float constant = 1.0f;
    float linear = 0.09f;
    float quadratic = 0.032f;

    PointLight(Vec3 position);
    PointLight(Vec3 position, Vec3 color);
    PointLight(Vec3 position, Vec3 color, float constant, float linear, float quadratic);

    void upload(Shader &s, int index) const;
  };
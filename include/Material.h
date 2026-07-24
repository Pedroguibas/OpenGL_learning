#pragma once

#include <Shader.h>
#include <mat.h>

class Material {
  public:
    unsigned int diffuseIndex;
    unsigned int specularIndex;

    Vec3 specularColor = Vec3(1.0f, 1.0f, 1.0f);

    float specularIntensity = 0.5f;
    float shininess = 32.0f;

    Material(unsigned int diffuseIndex, unsigned int specularIndex);
    Material(unsigned int diffuseIndex, unsigned int specularIndex, Vec3 specularColor, float specularIntensity, float shininess);

    void bind(Shader &s) const;
};
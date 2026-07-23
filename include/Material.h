#pragma once

#include <Texture.h>
#include <Shader.h>
#include <mat.h>

class Material {
  public:
    Texture &diffuseTexture;
    Texture &specularTexture;

    Vec3 specularColor = Vec3(1.0f, 1.0f, 1.0f);

    float specularIntensity = 0.5f;
    float shininess = 32.0f;

    Material(Texture &diffuseTexture, Texture &specularTexture);
    Material(Texture &diffuseTexture, Texture &specularTexture, Vec3 specularColor, float specularIntensity, float shininess);

    void bind(Shader &s) const;
};
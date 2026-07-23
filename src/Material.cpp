#include <Material.h>

Material::Material(Texture &diffuseTexture, Texture &specularTexture)
: diffuseTexture(diffuseTexture), specularTexture(specularTexture) {}

Material::Material(Texture &diffuseTexture, Texture &specularTexture, Vec3 specularColor, float specularIntensity, float shininess)
: diffuseTexture(diffuseTexture), specularTexture(specularTexture), specularColor(specularColor),
 specularIntensity(specularIntensity), shininess(shininess) {}

void Material::bind(Shader &s) const {
  diffuseTexture.bind(0);
  specularTexture.bind(1);

  s.setInt("material.diffuse", static_cast<int>(0));
  s.setInt("material.specular", static_cast<int>(1));

  s.setVec3("material.specularColor", specularColor);

  s.setFloat("material.specularIntensity", specularIntensity);

  s.setFloat("material.shininess", shininess);
}
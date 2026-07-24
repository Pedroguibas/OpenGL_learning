#include <Material.h>

Material::Material(unsigned int diffuseIndex, unsigned int specularIndex)
: diffuseIndex(diffuseIndex), specularIndex(specularIndex) {}

Material::Material(unsigned int diffuseIndex, unsigned int specularIndex, Vec3 specularColor, float specularIntensity, float shininess)
: diffuseIndex(diffuseIndex), specularIndex(specularIndex), specularColor(specularColor),
 specularIntensity(specularIntensity), shininess(shininess) {}

void Material::bind(Shader &s) const {
  s.setInt("material.diffuse", static_cast<int>(diffuseIndex));
  s.setInt("material.specular", static_cast<int>(specularIndex));

  s.setVec3("material.specularColor", specularColor);

  s.setFloat("material.specularIntensity", specularIntensity);

  s.setFloat("material.shininess", shininess);
}
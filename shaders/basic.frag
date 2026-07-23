#version 460 core

struct PointLight {
  vec3 position;
  vec3 color;

  float constant;
  float linear;
  float quadratic;
};

struct Material {
  vec3 specularColor;
  sampler2D diffuse;
  sampler2D specular;

  float specularIntensity;
  float shininess;
};

in vec2 texCoord;
in vec3 normal;
in vec3 fragmentPosition;

uniform vec3 lightDirection;
uniform vec3 lightColor;
uniform vec3 cameraPosition;

uniform float ambientStrength;

uniform PointLight lights[10];
uniform int pointLightCount;

uniform Material material;

out vec4 FragColor;

void main() {
  vec4 textureColor = texture(material.diffuse, texCoord);

  float reflectivity = texture(material.specular, texCoord).r;

  vec3 normalizedNormal = normalize(normal);
  vec3 directionToLight = normalize(-lightDirection);

  float diffuseStrength = max(dot(normalizedNormal, directionToLight), 0.0);

  vec3 ambient = ambientStrength * lightColor;
  
  vec3 viewDirection = normalize(cameraPosition - fragmentPosition);

  vec3 reflectedDirection = reflect(
    -directionToLight,
    normalizedNormal
  );

  float specularStrength = pow(
    max(
      dot(viewDirection, reflectedDirection),
      0.0
    ),
    material.shininess
  );

  vec3 diffuse = diffuseStrength * lightColor;

  vec3 specular = 
    material.specularIntensity *
    reflectivity *
    specularStrength *
    material.specularColor *
    lightColor;

  vec3 finalColor = textureColor.rgb * (ambient + diffuse) + specular;

  for (int i=0; i<pointLightCount; i++) {
    vec3 fragmentToLight = lights[i].position - fragmentPosition;

    float distanceToLight = length(fragmentToLight);

    vec3 directionToLight = normalize(fragmentToLight);

    diffuseStrength = max(dot(normalizedNormal, directionToLight), 0.0);


    reflectedDirection = reflect(
      -directionToLight,
      normalizedNormal
    );
    
    specularStrength = pow(
      max(
        dot(viewDirection, reflectedDirection),
        0.0
      ),
      material.shininess
    );

    diffuse = diffuseStrength * lights[i].color;

    specular = 
      material.specularIntensity *
      reflectivity *
      specularStrength *
      material.specularColor *
      lights[i].color;

    float attenuation = 1.0 / (
      lights[i].constant +
      lights[i].linear * distanceToLight +
      lights[i].quadratic * distanceToLight * distanceToLight
    );

    finalColor += textureColor.rgb * (diffuse + specular) * attenuation;
  }

  FragColor = vec4(finalColor, textureColor.a);
}
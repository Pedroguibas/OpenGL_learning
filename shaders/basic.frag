#version 460 core

struct PointLight {
  vec3 position;
  vec3 color;

  float constant;
  float linear;
  float quadratic;
};

in vec2 texCoord;
in vec3 normal;
in vec3 fragmentPosition;

uniform sampler2D texture1;

uniform vec3 lightDirection;
uniform vec3 lightColor;
uniform vec3 cameraPosition;

uniform float ambientStrength;
uniform float specularIntensity;
uniform float shininess;

uniform PointLight lights[10];
uniform int pointLightCount;

out vec4 FragColor;

void main() {
  vec4 textureColor = texture(texture1, texCoord);

  vec3 normalizedNormal = normalize(normal);
  vec3 directionToLight = normalize(-lightDirection);

  float diffuseStrength = max(dot(normalizedNormal, directionToLight), 0.0);

  vec3 ambient = ambientStrength * lightColor;

  vec3 diffuse = diffuseStrength * lightColor;
  
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
    shininess
  );

  vec3 specular = specularIntensity * specularStrength * lightColor;

  vec3 finalLighting = ambient + diffuse + specular;

  for (int i=0; i<pointLightCount; i++) {
    vec3 fragmentToLight = lights[i].position - fragmentPosition;

    float distanceToLight = length(fragmentToLight);

    vec3 directionToLight = normalize(fragmentToLight);

    diffuseStrength = max(dot(normalizedNormal, directionToLight), 0.0);

    diffuse = diffuseStrength * lights[i].color;

    reflectedDirection = reflect(
      -directionToLight,
      normalizedNormal
    );
    
    specularStrength = pow(
      max(
        dot(viewDirection, reflectedDirection),
        0.0
      ),
      shininess
    );

    specular = specularIntensity * specularStrength * lights[i].color;

    float attenuation = 1.0 / (
      lights[i].constant +
      lights[i].linear * distanceToLight +
      lights[i].quadratic * distanceToLight * distanceToLight
    );

    finalLighting += (diffuse + specular) * attenuation;
  }

  FragColor = vec4(textureColor.rgb * finalLighting, textureColor.a);
}
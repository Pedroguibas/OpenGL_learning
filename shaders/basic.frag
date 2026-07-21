#version 460 core

in vec2 texCoord;
in vec3 normal;

uniform sampler2D texture1;

uniform vec3 lightDirection;
uniform vec3 lightColor;
uniform vec3 cmaeraPosition;

uniform float ambientStrength;
uniform float specularIntensity;
uniform float shininess;

out vec4 FragColor;

void main() {
  vec4 textureColor = texture(texture1, texCoord);
  vec3 viewDirection = normalize(cameraPosition - fragmentPosition);

  vec3 normalizedNormal = normalize(normal);
  vec3 directionToLight = normalize(-lightDirection);

  float diffuseStrength = max(dot(normalizedNormal, directionToLight), 0.0);

  vec3 ambient = ambientStrength * lightColor;

  vec3 diffuse = diffuseStrength * lightColor;

  vec3 finalLighting = ambient + diffuse;

  FragColor = vec4(textureColor.rgb * finalLighting, textureColor.a);
}
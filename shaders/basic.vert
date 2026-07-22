#version 460 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in vec3 aNormal;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 mvp;

out vec2 texCoord;
out vec3 normal;
out vec3 fragmentPosition;

void main() {
  vec4 worldPosition = model * vec4(aPosition, 1.0);

  gl_Position = mvp * vec4(
    aPosition,
    1.0
  );
  texCoord = aTexCoord;
  fragmentPosition = worldPosition.xyz;

  normal = mat3(transpose(inverse(model))) * aNormal;
}
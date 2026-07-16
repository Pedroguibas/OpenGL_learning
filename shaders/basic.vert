#version 460 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec4 aColor;

uniform mat4 model;

out vec4 vertexColor;

void main() {
  gl_Position = model * vec4(
    aPosition,
    1.0
  );
  vertexColor = aColor;
}
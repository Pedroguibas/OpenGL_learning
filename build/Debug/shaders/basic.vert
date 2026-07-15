#version 460 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec4 aColor;

uniform vec3 offset;

out vec4 vertexColor;

void main() {
  gl_Position = vec4(
    aPosition + offset,
    1.0
  );
  vertexColor = aColor;
}
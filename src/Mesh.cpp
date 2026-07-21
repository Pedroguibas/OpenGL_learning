#include "Mesh.h"

Mesh::Mesh(float *vertexes, unsigned int *indices, GLsizei indiceCount, GLsizeiptr vertexBufferSize, GLsizei stride) 
: indiceCount(indiceCount), stride(stride) {
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

  glBufferData(
    GL_ARRAY_BUFFER,
    vertexBufferSize,
    vertexes,
    GL_STATIC_DRAW
  );

  glBufferData(
    GL_ELEMENT_ARRAY_BUFFER,
    indiceCount * sizeof(indices[0]),
    indices,
    GL_STATIC_DRAW
  );
}

void Mesh::draw() {
    // Binds VAO
    glBindVertexArray(VAO);

    glDrawElements(
      GL_TRIANGLES,
      indiceCount,
      GL_UNSIGNED_INT,
      nullptr
    );
}

Mesh Mesh::createColored(float *vertexes, unsigned int *indices, GLsizei indiceCount, GLsizeiptr vertexBufferSize) {
  Mesh mesh(vertexes, indices, indiceCount, vertexBufferSize, 7 * sizeof(float));
  
  mesh.addAttribute(
    0,
    3,
    GL_FLOAT,
    GL_FALSE,
    (void*)0
  );
  
  mesh.addAttribute(
    1,
    4,
    GL_FLOAT,
    GL_FALSE,
    (void*)(3 * sizeof(float))
  );
  
  return mesh;
}

Mesh Mesh::createTextured(float *vertexes, unsigned int *indices, GLsizei indiceCount, GLsizeiptr vertexBufferSize) {
  Mesh mesh(vertexes, indices, indiceCount, vertexBufferSize, 5 * sizeof(float));

  mesh.addAttribute(
    0,
    3,
    GL_FLOAT,
    GL_FALSE,
    (void*)0
  );

  mesh.addAttribute(
    1,
    2,
    GL_FLOAT,
    GL_FALSE,
    (void*)(3 * sizeof(float))
  );

  return mesh;
}

Mesh Mesh::box(float width, float height, float depth) {
  GLfloat h_width = width/2,
          h_height = height/2,
          h_depth = depth/2;
  
  // Defines cube vertices
  float vertices[] = {
    // Front
    -h_width, h_height, h_depth, 0.0f, 0.0f, // 0
    h_width, h_height, h_depth, 1.0f, 0.0f, // 1
    -h_width, -h_height, h_depth, 0.0f, 1.0f, // 2
    h_width, -h_height, h_depth, 1.0f, 1.0f, // 3

    // Back
    -h_width, -h_height, -h_depth, 0.0f, 0.0f, // 4
    h_width, -h_height, -h_depth, 1.0f, 0.0f, // 5
    -h_width, h_height, -h_depth, 0.0f, 1.0f, // 6
    h_width, h_height, -h_depth, 1.0f, 1.0f, // 7

    // Top
    -h_width, h_height, -h_depth, 0.0f, 0.0f, // 8
    h_width, h_height, -h_depth, 1.0f, 0.0f, // 9
    -h_width, h_height, h_depth, 0.0f, 1.0f, // 10
    h_width, h_height, h_depth, 1.0f, 1.0f, // 11

    // Bottom
    -h_width, -h_height, h_depth, 0.0f, 0.0f, // 12
    h_width, -h_height, h_depth, 1.0f, 0.0f, // 13
    -h_width, -h_height, -h_depth, 0.0f, 1.0f, // 14
    h_width, -h_height, -h_depth, 1.0f, 1.0f, // 15

    // Left
    -h_width, h_height, -h_depth, 0.0f, 0.0f, // 16
    -h_width, h_height, h_depth, 1.0f, 0.0f, // 17
    -h_width, -h_height, -h_depth, 0.0f, 1.0f, // 18
    -h_width, -h_height, h_depth, 1.0f, 1.0f, // 19

    // Right
    h_width, h_height, h_depth, 0.0f, 0.0f, // 20
    h_width, h_height, -h_depth, 1.0f, 0.0f, // 21
    h_width, -h_height, h_depth, 0.0f, 1.0f, // 22
    h_width, -h_height, -h_depth, 1.0f, 1.0f // 23
  };

  // Defines cube face triangle
  unsigned int indices[] = {
    0, 1, 2,
    1, 3, 2,

    4, 5, 6,
    5, 7, 6,

    8, 9, 10,
    9, 11, 10,

    12, 13, 14,
    13, 15, 14,

    16, 17, 18,
    17, 19, 18,

    20, 21, 22,
    21, 23, 22
  };

  return Mesh::createTextured(vertices, indices, sizeof(indices) / sizeof(indices[0]), sizeof(vertices));
}

Mesh::~Mesh()
{
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  glDeleteVertexArrays(1, &VAO);
}


void Mesh::addAttribute(GLuint index, GLuint size, GLenum type, GLboolean normalized, const void *pointer) {
  glBindVertexArray(VAO);

  glVertexAttribPointer(
    index,
    size,
    type,
    normalized,
    stride,
    pointer
  );

  glEnableVertexAttribArray(index);
}
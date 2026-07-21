#pragma once

#include <glad/gl.h>

class Mesh {
  public:
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
    GLsizei indiceCount;
    GLsizei stride;
    ~Mesh();
    Mesh(float *vertexes, unsigned int *indices, GLsizei indiceCount, GLsizeiptr vertexBufferSize, GLsizei stride);
    

    Mesh static createColored(float *vertexes, unsigned int *indices, GLsizei indiceCount, GLsizeiptr vertexBufferSize);
    Mesh static createTextured(float *vertexes, unsigned int *indices, GLsizei indiceCount, GLsizeiptr vertexBufferSize);
    Mesh static createLitTextured(float *vertexes, unsigned int *indices, GLsizei indiceCount, GLsizeiptr vertexBufferSize);
    Mesh static box(float width, float height, float depth);

    void addAttribute(GLuint index, GLuint size, GLenum type, GLboolean normalized, const void *pointer);
    
    void draw();
};
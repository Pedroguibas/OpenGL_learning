#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "Shader.h"
using std::cout;

void framebuffer_size_callback(
  GLFWwindow* window,
  int width,
  int height
) {
  glViewport(0, 0, width, height);
}

int main() {

  if (!glfwInit()) {
    cout << "Failed to initialize GLFW\n";
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(1280, 702, "OpenGL", nullptr, nullptr);

  if (!window) {
    cout << "Failed to create window\n";
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGL(glfwGetProcAddress)) {
    cout << "Failed to initialize GLAD\n";
    return -1;
  }

  cout << "OpenGL Version: " << glGetString(GL_VERSION) << '\n';

  glViewport(0, 0, 1280, 720);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glClearColor(0.1f, 0.2f, 0.3f, 1.0f);


  GLuint VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  GLuint VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  float vertices[] = {
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
  };

  glBufferData(
    GL_ARRAY_BUFFER,
    sizeof(vertices),
    vertices,
    GL_STATIC_DRAW
  );
  
  glVertexAttribPointer(
    0,
    3,
    GL_FLOAT,
    GL_FALSE,
    7 * sizeof(float),
    (void*)0
  );

  glEnableVertexAttribArray(0);

  glVertexAttribPointer(
    1,
    4,
    GL_FLOAT,
    GL_FALSE,
    7 * sizeof(float),
    (void*)(3 * sizeof(float))
  );

  glEnableVertexAttribArray(1);


  Shader *shader;
  try {
    shader = new Shader("shaders/basic.vert", "shaders/basic.frag");
  } catch (std::exception e) {
    cout << "Failed loading basic shaders:\n" << e.what();
    return -1;
  }

  float position[2] = {0.0, 0.5};
  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    
    shader->use();

    glBindVertexArray(VAO);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);

    glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}
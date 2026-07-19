#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>
#include "Shader.h"
#include "Camera.h"
#include "mat.h"
#include <Texture.h>
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

  glfwWindowHint(GLFW_DEPTH_BITS, 24);
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

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT);
  
  
  GLuint VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  GLuint EBO;
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

  GLuint VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  float vertices[] = {
    // Front
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, // 0
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, // 1
    -0.5f, -0.5f, 0.5f, 0.0f, 1.0f, // 2
    0.5f, -0.5f, 0.5f, 1.0f, 1.0f, // 3

    // Back
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // 4
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, // 5
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, // 6
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f, // 7

    // Top
    -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, // 8
    0.5f, 0.5f, -0.5f, 1.0f, 0.0f, // 9
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, // 10
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f, // 11

    // Bottom
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // 12
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f, // 13
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // 14
    0.5f, -0.5f, -0.5f, 1.0f, 1.0f, // 15

    // Left
    -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, // 16
    -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, // 17
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // 18
    -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, // 19

    // Right
    0.5f, 0.5f, 0.5f, 0.0f, 0.0f, // 20
    0.5f, 0.5f, -0.5f, 1.0f, 0.0f, // 21
    0.5f, -0.5f, 0.5f, 0.0f, 1.0f, // 22
    0.5f, -0.5f, -0.5f, 1.0f, 1.0f // 23
  };

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

  glBufferData(
    GL_ARRAY_BUFFER,
    sizeof(vertices),
    vertices,
    GL_STATIC_DRAW
  );

  glBufferData(
    GL_ELEMENT_ARRAY_BUFFER,
    sizeof(indices),
    indices,
    GL_STATIC_DRAW
  );

  
  glVertexAttribPointer(
    0,
    3,
    GL_FLOAT,
    GL_FALSE,
    5 * sizeof(float),
    (void*)0
  );

  glEnableVertexAttribArray(0);

  glVertexAttribPointer(
    1,
    2,
    GL_FLOAT,
    GL_FALSE,
    5 * sizeof(float),
    (void*)(3 * sizeof(float))
  );

  glEnableVertexAttribArray(1);

  Texture tex("textures/stooped.jpg");
  tex.bind(0);

  Shader *shader;
  try {
    shader = new Shader("shaders/basic.vert", "shaders/basic.frag");
  } catch (std::exception e) {
    cout << "Failed loading basic shaders:\n" << e.what();
    return -1;
  }

  Camera cam(Vec3(0,3,3));
  
  int window_w;
  int window_h;

  
  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwGetFramebufferSize(window, &window_w, &window_h);
    float time = glfwGetTime();
    
    shader->use();
    shader->setInt("texture1", 0);
    
    cam.position = Vec3(3*std::cos(time * 1), 3, 3*std::sin(time * 1));
    cam.lookAt(Vec3(0,0,-0.1));

    Mat4 model = scale(2, 2, 2) * rotationX(time * 90);
    Mat4 view = cam.getViewMatrix();
    Mat4 projection = cam.getProjectionMatrix(window_w, window_h);
    Mat4 mvp = projection * view * model;

    shader->setMat4("model", model);
    shader->setMat4("view", view);
    shader->setMat4("projection", projection);
    shader->setMat4("mvp", mvp);


    glBindVertexArray(VAO);

    glDrawElements(
      GL_TRIANGLES,
      sizeof(indices) / sizeof(indices[0]),
      GL_UNSIGNED_INT,
      nullptr
    );  

    glfwSwapBuffers(window);

    glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}
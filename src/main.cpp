#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>
#include "Shader.h"
#include "Camera.h"
#include "mat.h"
#include "Mesh.h"
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

  // Initializes GLFW
  if (!glfwInit()) {
    cout << "Failed to initialize GLFW\n";
    return -1;
  }

  // Sets up GLFW
  glfwWindowHint(GLFW_DEPTH_BITS, 24);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


  // Creates window
  GLFWwindow* window = glfwCreateWindow(1280, 702, "OpenGL", nullptr, nullptr);

  if (!window) {
    cout << "Failed to create window\n";
    glfwTerminate();
    return -1;
  }

  // Makes window current context
  glfwMakeContextCurrent(window);

  // Initializes GLAD
  if (!gladLoadGL(glfwGetProcAddress)) {
    cout << "Failed to initialize GLAD\n";
    return -1;
  }
  cout << "OpenGL Version: " << glGetString(GL_VERSION) << '\n';

  // Sets function to run on window size change that updates viewport
  glViewport(0, 0, 1280, 720);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


  // Sets the background color
  glClearColor(0.1f, 0.2f, 0.3f, 1.0f);

  // Configures rendering
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT);


  // Defines cube vertices
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

  // Mesh cube = Mesh::createTextured(vertices, indices, 36, sizeof(vertices));
  Mesh cube = Mesh::box(1.0f, 1.0f, 1.0f);

  // Initializes Texture
  Texture *tex;
  try {
    tex = new Texture("textures/stooped.jpg");
  } catch (std::exception e) {
    cout << "Failed to load texture:\n" << e.what();
  }
  tex->bind(0);

  // Initializes Basic Shaders
  Shader *shader;
  try {
    shader = new Shader("shaders/basic.vert", "shaders/basic.frag");
  } catch (std::exception e) {
    cout << "Failed to load basic shaders:\n" << e.what();
    return -1;
  }

  // Initializes camera
  Camera cam(Vec3(0,3,3));
  
  int window_w;
  int window_h;

  
  // Window loop
  while (!glfwWindowShouldClose(window)) {
    // Clears color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Gets window dimantions and store them in local variables
    glfwGetFramebufferSize(window, &window_w, &window_h);

    // gets time
    float time = glfwGetTime();
    
    // binds shaders
    shader->use();

    // sets current texture on GPU
    shader->setInt("texture1", 0);
    
    // updates cam positions
    cam.position = Vec3(3*std::cos(time * 1), 3, 3*std::sin(time * 1));

    // updates cam orientation
    cam.lookAt(Vec3(0,0,-0.1));

    // sets up MVP matrix
    Mat4 model = scale(2, 2, 2) * rotationX(time * 90);
    Mat4 view = cam.getViewMatrix();
    Mat4 projection = cam.getProjectionMatrix(window_w, window_h);
    Mat4 mvp = projection * view * model;

    // sends matrices to GPU
    shader->setMat4("model", model);
    shader->setMat4("view", view);
    shader->setMat4("projection", projection);
    shader->setMat4("mvp", mvp);

    cube.draw();
    
    glfwSwapBuffers(window);

    glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}
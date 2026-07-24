#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>
#include "Shader.h"
#include "Camera.h"
#include "mat.h"
#include "Mesh.h"
#include <PointLight.h>
#include <Texture.h>
#include <Material.h>
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

  // defines ground vertexes 
  float groundV[] = {
    -50.0f, 0.0f, -50.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    50.0f, 0.0f, -50.0f, 10.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    -50.0f, 0.0f, 50.0f, 0.0f, 10.0f, 0.0f, 1.0f, 0.0f,
    50.0f, 0.0f, 50.0f, 10.0f, 10.0f, 0.0f, 1.0f, 0.0f
  };

  GLuint groundI[] = {
    0, 1, 2,
    1, 3, 2
  };


  Mesh cube1 = Mesh::box(1.0f, 1.0f, 1.0f);
  Mesh cube2 = Mesh::box(1.0f, 1.0f, 1.0f);
  Mesh ground = Mesh::createLitTextured(groundV, groundI, 6, sizeof(groundV));

  // Initializes Texture
  Texture *tex, *groundTex, *boxDiffuse, *boxSpecular, *defaultSpecular;
  try {
    tex = new Texture("textures/stooped.jpg");
    groundTex = new Texture("textures/ground.jpg");
    boxDiffuse = new Texture("textures/box_diffuse.png");
    boxSpecular = new Texture("textures/box_specular.png");
    defaultSpecular = new Texture("textures/default_specular.png");
  } catch (std::exception &e) {
    cout << "Failed to load texture:\n" << e.what();
  }
  tex->bind(0);
  groundTex->bind(1);
  boxDiffuse->bind(2);
  boxSpecular->bind(3);
  defaultSpecular->bind(4);

  // Initializes Basic Shaders
  Shader *shader;
    try {
      shader = new Shader(
          "shaders/basic.vert",
          "shaders/basic.frag"
      );
  }
  catch (const std::exception& e) {
      cout
          << "Failed to load basic shaders:\n"
          << e.what()
          << '\n';

      return -1;
  }

  // Initializes camera
  Camera cam(Vec3(0,2,2));
  
  int window_w;
  int window_h;

  PointLight pl1(Vec3(1.0f, 1.0f, 1.0f), Vec3(0.1f, 0.3f, 1.0f));
  PointLight pl2(Vec3(-1.0f, 1.0f, 1.0f), Vec3(1.0f, 0.3f, 0.1f));
  
  shader->use();
  
  pl1.upload(*shader, 0);
  pl2.upload(*shader, 1);
  
  shader->setInt("pointLightCount", 2);

  Material metalFloor(1, 4, Vec3(1.0f, 1.0f, 1.0f), 1.0f, 128.0f);
  Material boxMaterial(2, 3, Vec3(1.0f, 1.0f, 1.0f), 0.5f, 24.0f);
  
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
    
    // sets up ground MVP matrix
    Mat4 model;
    Mat4 view = cam.getViewMatrix();
    Mat4 projection = cam.getProjectionMatrix(window_w, window_h);
    Mat4 mvp = projection * view * model;

    // sends ground mvp
    shader->setMat4("model", model);
    shader->setMat4("view", view);
    shader->setMat4("projection", projection);
    shader->setMat4("mvp", mvp);

    // sets light properties
    shader->setVec3(
      "lightDirection",
      1.0f,
      -1.0f,
      1.0f
    );
    shader->setFloat("ambientStrength", 0.25f);
    shader->setVec3(
      "lightColor",
      1.0f,
      1.0f,
      1.0f
    );
    shader->setVec3(
      "cameraPosition",
      cam.position.x,
      cam.position.y,
      cam.position.z
    );

    metalFloor.bind(*shader);

    ground.draw();

    
    // updates cam positions
    cam.position = Vec3(3*std::cos(time * 1), 3, 3*std::sin(time * 1));

    // updates cam orientation
    cam.lookAt(Vec3(0,0,0));

    // sets first cube model and mvp
    model = translate(Vec3(-0.7, 0.5, 0));
    mvp = projection * view * model;
    
    

    // sends first cube mvp
    shader->setMat4("model", model);
    shader->setMat4("mvp", mvp);

    boxMaterial.bind(*shader);

    cube1.draw();
    
    // sets second cube material properties
    model = translate(Vec3(0.7, 0.5, 0));
    mvp = projection * view * model;

    // sends second cube mvp
    shader->setMat4("model", model);
    shader->setMat4("mvp", mvp);

    cube2.draw();

    glfwSwapBuffers(window);

    glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}
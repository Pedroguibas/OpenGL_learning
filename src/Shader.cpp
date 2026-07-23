#include "Shader.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <filesystem>


Shader::Shader(const string& vertexPath, const string&fragmentPath) {
  // Gets files as strings
  string vertexSrc = Shader::readFile(vertexPath);
  string fragmentSrc = Shader::readFile(fragmentPath);

  // Compile both shaders
  GLuint vertexShader = Shader::compileShader(GL_VERTEX_SHADER, vertexSrc.c_str());
  GLuint fragmentShader = Shader::compileShader(GL_FRAGMENT_SHADER, fragmentSrc.c_str());

  m_ID = linkProgram(vertexShader, fragmentShader);

  // Deletes shaders in CPU after sending them to GPU
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}
Shader::~Shader() {
  glDeleteProgram(m_ID);
}

void Shader::use() const {
  glUseProgram(m_ID);
}

GLuint Shader::compileShader(const GLenum type, const char* src) {
  // Creates shader
  GLuint shader = glCreateShader(type);

  glShaderSource(
    shader,
    1,
    &src,
    nullptr
  );
  // compiles the shader
  glCompileShader(shader);

  // checks for success
  GLint success;
  glGetShaderiv(
    shader,
    GL_COMPILE_STATUS,
    &success
  );

  if (!success) {
    char infoLog[512];

    glGetShaderInfoLog(
      shader,
      512,
      nullptr,
      infoLog
    );

    if (type == GL_VERTEX_SHADER) {
      throw std::runtime_error(
        string("Vertex shader compilation failed:\n") +
        infoLog
      );
    } else {
      throw std::runtime_error(
        string("Fragment shader compilation failed:\n") +
        infoLog
      );
    }
  }

  // returns shader id
  return shader;
}

GLuint Shader::linkProgram(GLuint vertexShader, GLuint fragmentShader) {
  // creates program
  GLuint program = glCreateProgram();

  // attaches shaders to program
  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);

  // links program to context
  glLinkProgram(program);

  // checks for success;
  GLint success;
  glGetProgramiv(program, GL_LINK_STATUS, &success);

  if (!success) {
    char infoLog[512];

    glGetProgramInfoLog(
      program,
      512,
      nullptr,
      infoLog
    );

    glDeleteProgram(program);

    throw std::runtime_error(
      string("Shader program linking failed:\n") +
      infoLog
    );
  }

  return program;
}


// returns file as string
string Shader::readFile(const string &path) {
  std::cout << "Opening shader: " << path << '\n';
  std::ifstream file(path);

  if (!file.is_open()) {
    throw std::runtime_error(
      "Failed to open shader: " + path
    );
  }

  
  std::stringstream buffer;

  buffer << file.rdbuf();

  return buffer.str();
}

GLint Shader::getUniformLocation(const string &name) {
  auto it = m_uniformLocations.find(name);

  if (it != m_uniformLocations.end()) {
    return it->second;
  } 

  GLint location = glGetUniformLocation(
    m_ID,
    name.c_str()
  );

  m_uniformLocations[name] = location;

  return location;
}




void Shader::setFloat(const string &name, const float val) {
  GLint location = getUniformLocation(name);

  glUniform1f(location, val);
}

void Shader::setVec2(const string &name, const float val1, const float val2) {
  GLint location = getUniformLocation(name);

  glUniform2f(location, val1, val2);
}

void Shader::setVec3(const string &name, const float val1, const float val2, const float val3) {
  GLint location = getUniformLocation(name);

  glUniform3f(location, val1, val2, val3);
}

void Shader::setVec3(const string &name, const Vec3 v) {
  GLint location = getUniformLocation(name);

  glUniform3f(location, v.x, v.y, v.z);
}

void Shader::setVec4(const string &name, const float val1, const float val2, const float val3, const float val4) {
  GLint location = getUniformLocation(name);

  glUniform4f(location, val1, val2, val3, val4);
}

void Shader::setVec4(const string &name, const Vec4 v) {
  GLint location = getUniformLocation(name);

  glUniform4f(location, v.x, v.y, v.z, v.w);
}

void Shader::setMat4(const string &name, const float *mat) {
  GLint location = getUniformLocation(name);

  glUniformMatrix4fv(location, 1, GL_TRUE, mat);
}

void Shader::setMat4(const string &name, const Mat4 &mat) {
  GLint location = getUniformLocation(name);

  glUniformMatrix4fv(location, 1, GL_TRUE, &mat.m[0][0]);
}

void Shader::setInt(const string &name, const int val) {
  GLint location = getUniformLocation(name);

  glUniform1i(location, val);
}
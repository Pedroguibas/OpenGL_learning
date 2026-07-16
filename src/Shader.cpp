#include "Shader.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <filesystem>


Shader::Shader(const string& vertexPath, const string&fragmentPath) {
  string vertexSrc = Shader::readFile(vertexPath);
  string fragmentSrc = Shader::readFile(fragmentPath);

  GLuint vertexShader = Shader::compileShader(GL_VERTEX_SHADER, vertexSrc.c_str());
  GLuint fragmentShader = Shader::compileShader(GL_FRAGMENT_SHADER, fragmentSrc.c_str());

  m_ID = linkProgram(vertexShader, fragmentShader);

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
GLuint shader = glCreateShader(type);

  glShaderSource(
    shader,
    1,
    &src,
    nullptr
  );

  glCompileShader(shader);

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

  return shader;
}

GLuint Shader::linkProgram(GLuint vertexShader, GLuint fragmentShader) {
  GLuint program = glCreateProgram();

  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);

  glLinkProgram(program);

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

string Shader::readFile(const string &path) {
  std::cout << "Opening shader: " << path << '\n';
  std::ifstream file(path);

  
  std::cout << std::filesystem::current_path() << '\n';

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

void Shader::setVec4(const string &name, const float val1, const float val2, const float val3, const float val4) {
  GLint location = getUniformLocation(name);

  glUniform4f(location, val1, val2, val3, val4);
}

void Shader::setMat4(const string &name, const float *mat) {
  GLint location = getUniformLocation(name);

  glUniformMatrix4fv(location, 1, GL_TRUE, mat);
}

void Shader::setMat4(const string &name, const Mat4 &mat) {
  GLint location = getUniformLocation(name);

  glUniformMatrix4fv(location, 1, GL_TRUE, &mat.m[0][0]);
}


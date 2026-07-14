#pragma once

#include <glad/gl.h>

#include <string>
using std::string;

class Shader {
private:
  GLuint m_ID{};

  static string readFile(const string &path);
  static GLuint compileShader(const GLenum type, const char *src);
  static GLuint linkProgram(GLuint vertexShader, GLuint fragmentShader);

public:
  Shader(const string &vertexPath, const string &fragmentPath);
  ~Shader();

  Shader(const Shader &) = delete;
  Shader &operator=(const Shader &) = delete;
  Shader(Shader &&other) noexcept;
  Shader &operator=(Shader &&other) noexcept;

  void use() const;
};
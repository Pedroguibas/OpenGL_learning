#pragma once

#include <glad/gl.h>

#include <string>
#include <unordered_map>
#include "mat.h"
using std::string;
using std::unordered_map;

class Shader {
private:
  GLuint m_ID{};
  unordered_map<string, GLuint> m_uniformLocations;

  static string readFile(const string &path);
  static GLuint compileShader(const GLenum type, const char *src);
  static GLuint linkProgram(GLuint vertexShader, GLuint fragmentShader);
  GLint getUniformLocation(const string &name);

public:
  Shader(const string &vertexPath, const string &fragmentPath);
  ~Shader();

  Shader(const Shader &) = delete;
  Shader &operator=(const Shader &) = delete;
  Shader(Shader &&other) noexcept;
  Shader &operator=(Shader &&other) noexcept;

  void setFloat(const string &name, const float val);
  void setVec2(const string &name, const float val1, const float val2);
  void setVec3(const string &name, const float val1, const float val2, const float val3);
  void setVec4(const string &name, const float val1, const float val2, const float val3, const float val4);
  void setMat4(const string &name, const float *mat);
  void setMat4(const string &name, const Mat4 &mat);

  void use() const;
};
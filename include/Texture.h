#pragma once

#include <string>
#include <glad/gl.h>
using std::string;

class Texture {
  private:
    GLuint id;
    int width;
    int height;
    int channels;
    
  public:
    Texture(string file);
    ~Texture();

    void bind(unsigned int unit) const;
    void unbind() const;
    void printInfo();
};
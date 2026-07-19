#include "Texture.h"
#include <stb_image.h>
#include <stdexcept>
#include <iostream>

Texture::Texture(string file) {
    unsigned char* data = stbi_load(
    file.c_str(),
    &width,
    &height,
    &channels,
    0
  );

  if (!data) {
    throw std::runtime_error(
      string("Not able to locate texture: ") +
      file
    );
  }

  GLenum format;
  switch (channels) {
    case 1:
      format = GL_RED;
      break;
    
    case 3:
      format = GL_RGB;
      break;
    
    case 4:
      format = GL_RGBA;
      break;
    
    default:
    throw std::runtime_error("Unsupported texture format.");
  }

  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);

  glTexParameteri(
    GL_TEXTURE_2D,
    GL_TEXTURE_WRAP_S,
    GL_REPEAT
);

glTexParameteri(
    GL_TEXTURE_2D,
    GL_TEXTURE_WRAP_T,
    GL_REPEAT
);

glTexParameteri(
    GL_TEXTURE_2D,
    GL_TEXTURE_MIN_FILTER,
    GL_LINEAR_MIPMAP_LINEAR
);

glTexParameteri(
    GL_TEXTURE_2D,
    GL_TEXTURE_MAG_FILTER,
    GL_LINEAR
);

  glTexImage2D(
    GL_TEXTURE_2D,
    0,
    format,
    width,
    height,
    0,
    format,
    GL_UNSIGNED_BYTE,
    data
  );

  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(data);
}

Texture::~Texture() {
  glDeleteTextures(1, &id);
}

void Texture::printInfo() {
  std::cout
    << width << " "
    << height << " "
    << channels
    << '\n';
}

void Texture::bind(unsigned int unit) const {
  glActiveTexture(GL_TEXTURE0 + unit);
  glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::unbind() const {
  glBindTexture(GL_TEXTURE_2D, 0);
}
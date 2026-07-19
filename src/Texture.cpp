#include "Texture.h"
#include <stb_image.h>
#include <stdexcept>
#include <iostream>

Texture::Texture(string file) {
  // reads texture file and gets metadata
  unsigned char* data = stbi_load(
    file.c_str(),
    &width,
    &height,
    &channels,
    0
  );

  // throws error if file could not be read
  if (!data) {
    throw std::runtime_error(
      string("Not able to locate texture: ") +
      file
    );
  }

  // converts int to gl constants
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

  // generates and binds texture
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);

  // set up texture params
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

  // sends texture to GPU
  glTexImage2D(
    GL_TEXTURE_2D, // texture type
    0, // level
    format, // format in cpu
    width,
    height,
    0, //border size
    format, //format in gpu
    GL_UNSIGNED_BYTE, // type
    data // pixels
  );

  // generate texture map
  glGenerateMipmap(GL_TEXTURE_2D);

  // deletes texture data in CPU after sending it to GPU
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
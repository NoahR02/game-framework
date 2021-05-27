#include <glad/glad.h>
#include <stb_image/stb_image.h>
#include "Texture.h"

Texture::Texture(const std::string &texturePath) {
  glGenTextures(1, &rendererID);

  unsigned int slot = 0;
  glActiveTexture(GL_TEXTURE0 + slot);
  glBindTexture(GL_TEXTURE_2D, rendererID);

  int width = 0, height = 0, bpp = 0;
  stbi_set_flip_vertically_on_load(true);
  unsigned char* textureData = stbi_load(texturePath.c_str(), &width, &height, &bpp, 4);
  this->width = width;
  this->height = height;

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // s is x
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // t is y
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
  unBind();
  stbi_image_free(textureData);
}

void Texture::bind(unsigned int slot) {
  glActiveTexture(GL_TEXTURE0 + slot);
  glBindTexture(GL_TEXTURE_2D, rendererID);
}

void Texture::unBind() {
  glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture() {
  glDeleteTextures(1, &rendererID);
}

#include <glad/glad.h>
#include "Texture.h"
#include <stb_image/stb_image.h>

Texture::Texture(std::string &filePath) {
  glGenTextures(1, &rendererID);
  bind();
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // s is x
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // t is y
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  stbi_set_flip_vertically_on_load(true);
  const char* filePathSource = filePath.c_str();
  unsigned char* imageData = stbi_load(filePathSource, &width, &height, &nrChannels, 4);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
  stbi_image_free(imageData);
  unBind();
}

void Texture::bind() {
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, rendererID);
}

void Texture::unBind() {
  glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture() {
  unBind();
  glDeleteTextures(1, &rendererID);
}
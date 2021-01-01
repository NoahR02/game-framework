#ifndef MINECRAFTCLONE_TEXTURE_H
#define MINECRAFTCLONE_TEXTURE_H


#include <string>

struct Texture {
  unsigned int rendererID;
  int nrChannels;

  int width, height;
  unsigned char* imageData;
  bool needsFreed = false;
  Texture() = default;
  Texture(std::string& filePath);
  Texture(unsigned char* data, int width, int height);
  void bind();
  void unBind();
  ~Texture();
};


#endif //MINECRAFTCLONE_TEXTURE_H

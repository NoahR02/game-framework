#ifndef MINECRAFTCLONE_TEXTURE_H
#define MINECRAFTCLONE_TEXTURE_H


#include <string>

class Texture {
private:
  unsigned int rendererID;
  int width, height, nrChannels;

public:
  Texture(std::string& filePath);
  void bind();
  void unBind();
  ~Texture();
};


#endif //MINECRAFTCLONE_TEXTURE_H

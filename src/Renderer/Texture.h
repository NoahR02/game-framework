#ifndef RPG_TEXTURE_H
#define RPG_TEXTURE_H

#include <string>

struct Texture {

  unsigned int rendererID;

  int width, height;
  Texture(const std::string& texturePath);

  void bind(unsigned int slot = 0);
  void unBind();

  ~Texture();

};


#endif //RPG_TEXTURE_H

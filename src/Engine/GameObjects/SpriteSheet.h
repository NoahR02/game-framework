#ifndef RPG_SPRITESHEET_H
#define RPG_SPRITESHEET_H

#include <memory>
#include "../Renderer/Texture.h"


struct SpriteSheet {

  Texture* spriteSheet;

  SpriteSheet(std::string spriteSheetPath);

  Texture* getSprite(int width, int height, int x, int y) const;

  ~SpriteSheet();

};


#endif //RPG_SPRITESHEET_H

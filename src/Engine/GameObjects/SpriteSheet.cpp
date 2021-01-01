#include <iostream>
#include "SpriteSheet.h"
#include <cstring>

SpriteSheet::SpriteSheet(std::string spriteSheetPath) {
  spriteSheet = new Texture(spriteSheetPath);
}

Texture* SpriteSheet::getSprite(int width, int height, int x, int y) const {
  unsigned char buffer[16*16*4];

  y = spriteSheet->height/16 - y - 1;

  if((x < 0 || x >= spriteSheet->width/16) || (y < 0 || y >= spriteSheet->height/16))
    throw std::runtime_error("Invalid sprite position.");

  int startingPoint = (x * 4 * 16) + y * (spriteSheet->width * 4) * 16;

  for(int i = 0; i < 16; ++i)
    memcpy(buffer + i*16*4, spriteSheet->imageData + startingPoint + i * spriteSheet->width*4, 16 * 4);

  return new Texture(buffer, width, height);
}

SpriteSheet::~SpriteSheet() {
  std::cout << "Deleting Sprite Sheet" << std::endl;
  delete spriteSheet;
}

#ifndef RPG_SPRITE_H
#define RPG_SPRITE_H


#include "TextureRectangle.h"
#include "Color.h"

struct Sprite {

  float x;
  float y;

  float width;
  float height;

  TextureRectangle texturePosition;
  Color color;

};

#endif //RPG_SPRITE_H

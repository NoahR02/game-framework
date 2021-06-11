#ifndef RPG_SPRITESHEET_H
#define RPG_SPRITESHEET_H


#include <unordered_map>
#include "TileType.h"
#include "../TextureRectangle.h"

struct SpriteSheet {

  std::unordered_map<TileType, TextureRectangle> tileSpriteMap;

  void addTile(TileType tileType, TextureRectangle texturePosition);
  TextureRectangle getTile(TileType tileType);

};


#endif //RPG_SPRITESHEET_H

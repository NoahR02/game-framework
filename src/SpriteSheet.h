#ifndef RPG_SPRITESHEET_H
#define RPG_SPRITESHEET_H


#include <unordered_map>
#include "TileMap/TileType.h"
#include "TexturePosition.h"

struct SpriteSheet {

  std::unordered_map<TileType, TexturePosition> tileSpriteMap;

  void addTile(TileType tileType, TexturePosition texturePosition);
  TexturePosition getTile(TileType tileType);

};


#endif //RPG_SPRITESHEET_H

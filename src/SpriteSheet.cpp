#include "SpriteSheet.h"

void SpriteSheet::addTile(TileType tileType, TexturePosition texturePosition) {
  tileSpriteMap.insert({tileType, texturePosition});
}

TexturePosition SpriteSheet::getTile(TileType tileType) {
  return tileSpriteMap[tileType];
}
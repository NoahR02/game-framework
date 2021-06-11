#include "SpriteSheet.h"

void SpriteSheet::addTile(TileType tileType, TextureRectangle texturePosition) {
  tileSpriteMap.insert({tileType, texturePosition});
}

TextureRectangle SpriteSheet::getTile(TileType tileType) {
  return tileSpriteMap[tileType];
}
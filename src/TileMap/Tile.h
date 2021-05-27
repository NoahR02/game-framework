#ifndef RPG_TILE_H
#define RPG_TILE_H


#include "../Position.h"
#include "TileType.h"

class Tile {
public:
  Position position {50, 50};
  TileType tileType;
};


#endif //RPG_TILE_H

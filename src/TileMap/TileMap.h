#ifndef RPG_TILEMAP_H
#define RPG_TILEMAP_H


#include <memory>
#include <cista/containers/vector.h>
#include "../Renderer/VertexArray.h"
#include "../Renderer/VertexBuffer.h"
#include "../Renderer/ElementBuffer.h"
#include "../Renderer/Texture.h"
#include "../Renderer/ShaderProgram.h"
#include "../SpriteSheet.h"
#include "Tile.h"
#include "../Renderer/Camera.h"

class TileMap {
public:

  int tileMapWidth = 256;
  int tileMapHeight = 256;
  int tileWidth = 16;
  int tileHeight = 16;

  std::unique_ptr<VertexArray> tileMapVAO;
  std::unique_ptr<VertexBuffer> tileMapVBO;
  std::unique_ptr<ElementBuffer> tileMapEBO;
  std::unique_ptr<Texture> tileMapTexture;
  std::unique_ptr<ShaderProgram> defaultShaderProgram;

  SpriteSheet spriteSheet;
  std::vector<float> vertices;
  std::vector<unsigned int> indices;
  cista::basic_vector<Tile> tiles;

  TileMap(SpriteSheet spriteSheet);

  void addTile(Tile tile);
  void upload();
  void draw(const Camera& camera);
};


#endif //RPG_TILEMAP_H

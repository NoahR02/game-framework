#include "TileMap.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

TileMap::TileMap(SpriteSheet spriteSheet) : spriteSheet(spriteSheet)  {
    tileMapVAO = std::make_unique<VertexArray>();
    tileMapVAO->bind();

    tileMapVBO = std::make_unique<VertexBuffer>();
    tileMapVBO->bind();

    tileMapEBO = std::make_unique<ElementBuffer>();
    tileMapEBO->bind();

    defaultShaderProgram = std::make_unique<ShaderProgram>("shaders/defaultVertex.vert", "shaders/defaultFragment.frag");

    tileMapTexture = std::make_unique<Texture>("assets/tiny-16-basic/basictiles.png");
    tileMapTexture->bind();
}

void TileMap::addTile(Tile tile) {
  for(int i = 0; i < tiles.size(); ++i)
    if(tiles[i].position.x == tile.position.x && tiles[i].position.y == tile.position.y) {
      tiles.erase(&tiles[i]);
      tiles.push_back(tile);
      return;
    }

    tiles.push_back(tile);
}

void TileMap::upload() {
  vertices.clear();
  indices.clear();

  vertices.reserve(tiles.size() * (5 * 4));
  indices.reserve(tiles.size() * 6);

  unsigned int tmp = 0;

  float columns = tileMapTexture->width / tileWidth;
  float rows = tileMapTexture->height / tileHeight;


  for(int i = 0; i < tiles.size(); ++i) {
    TexturePosition texPos = spriteSheet.getTile(tiles[i].tileType);

    texPos.texturePosY = rows - texPos.texturePosY - 1;

    vertices.insert(vertices.end(), {
      //* Vertices *//*                                                                                                         *//* Texture Coords *//*
      /* top left */     static_cast<float>(tiles[i].position.x), static_cast<float>(tiles[i].position.y), 0.0f, static_cast<float>(texPos.texturePosX) / columns,
                         static_cast<float>(( static_cast<float>(texPos.texturePosY) + 1.0f)) / rows,  // top left
      /* bottom left */  static_cast<float>(tiles[i].position.x), static_cast<float>(tiles[i].position.y+tileHeight), 0.0f, static_cast<float>(texPos.texturePosX) / columns,
                         static_cast<float>(texPos.texturePosY) / rows,  // bottom left
      /* top right */    static_cast<float>(tiles[i].position.x+tileWidth), static_cast<float>(tiles[i].position.y), 0.0f, static_cast<float>((texPos.texturePosX + 1.0f)) / columns,
                         static_cast<float>(( static_cast<float>(texPos.texturePosY) + 1.0f)) / rows,  // top right
      /* bottom right */ static_cast<float>(tiles[i].position.x+tileWidth), static_cast<float>(tiles[i].position.y+tileHeight), 0.0f, static_cast<float>((texPos.texturePosX + 1.0f)) / columns,
                         static_cast<float>(texPos.texturePosY) / rows  // bottom right
    });

    indices.insert(indices.end(), {
      tmp + 0, tmp + 1, tmp + 2,
      tmp + 2, tmp + 1, tmp + 3
    });


    tmp += 4; // increase vertices
  }

  tileMapVAO->bind();
  tileMapVBO->bind();
  tileMapVBO->fillBuffer(vertices);

  tileMapEBO->bind();
  tileMapEBO->fillBuffer(indices);

  tileMapVAO->enableAttribute(0);
  tileMapVAO->describeAttributeLayout(0, 3, GL_FLOAT, false, sizeof(float) * 5, 0);

  tileMapVAO->enableAttribute(1);
  tileMapVAO->describeAttributeLayout(1, 2, GL_FLOAT, false, sizeof(float) * 5, sizeof(float) * 3);
}

void TileMap::draw(const Camera& camera) {
  tileMapVAO->bind();
  defaultShaderProgram->bind();
  tileMapVBO->bind();
  tileMapEBO->bind();
  tileMapTexture->bind();

  defaultShaderProgram->setUniformMatrix4fv("uMVP", 1, false, &camera.mvp[0][0]);
  defaultShaderProgram->setUniform1i("uTexture", 0);

  if(!indices.empty()) glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, nullptr);
}
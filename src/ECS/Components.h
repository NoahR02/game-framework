#ifndef RPG_COMPONENTS_H
#define RPG_COMPONENTS_H


#include <memory>

#include <entt/entt.hpp>

#include "../Renderer/VertexArray.h"
#include "../Renderer/VertexBuffer.h"
#include "../Renderer/ElementBuffer.h"
#include "../Renderer/Texture.h"
#include "../Renderer/ShaderProgram.h"

#include "../TileMap/Tile.h"
#include "../TileMap/SpriteSheet.h"
#include "../Window.h"


namespace Components {

  struct Controller {
    bool active;
  };

  struct TileMap {
    
    std::vector<Tile> tiles;
    SpriteSheet spriteSheet;
    int tileWidth;
    int tileHeight;

    TileMap(int tileWidth, int tileHeight);
  };

  struct StaticRenderGroup {

    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    std::unique_ptr<VertexArray> vao;
    std::unique_ptr<VertexBuffer> vbo;
    std::unique_ptr<ElementBuffer> ebo;
    std::shared_ptr<Texture> texture;
    std::unique_ptr<ShaderProgram> shaderProgram;


    StaticRenderGroup(const std::string& texturePath);

  };

};


#endif //RPG_COMPONENTS_H

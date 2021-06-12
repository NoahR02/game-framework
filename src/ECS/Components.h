#ifndef RPG_COMPONENTS_H
#define RPG_COMPONENTS_H


#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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


  struct Camera : Observer<Window> {
    float zoomLevel = 1.0f;
    float speed = 4.0f;
    float width;
    float height;

    glm::mat4 projection;
    glm::mat4 view;
    glm::mat4 mvp;


    Camera(float width, float height);

    void onNotify(Window &f, Event event) override;

    void setWidth(const float width) {
      this->width = width;
      projection = glm::ortho(0.0f, width/zoomLevel, height/zoomLevel, 0.0f);
      mvp = projection * view;
    }

    void setHeight(const float height) {
      this->height = height;
      projection = glm::ortho(0.0f, width/zoomLevel, height/zoomLevel,0.0f);
      mvp = projection * view;
    }

  };

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

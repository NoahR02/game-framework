#ifndef RPG_RENDERER_H
#define RPG_RENDERER_H

#include <vector>
#include "../ECS/Components.h"
#include "../ECS/Sprite.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Renderer {

  void beginDynamicBatch
  (

    glm::mat4& projectionMatrix,
    ShaderProgram& shaderProgram,
    Texture& textureAtlas

  );


  void endDynamicBatch();
  void draw(const Sprite& sprite);
  void draw(const Components::TileMap& tilemap);


  Renderer();

  std::vector<float> vertices{};
  std::vector<unsigned int> indices{};
  std::vector<const Sprite*> dynamicSprites{};

  glm::mat4* projectionMatrix;
  ShaderProgram* shaderProgram;
  Texture* texture;

  std::unique_ptr<VertexArray> vertexArray;
  std::unique_ptr<VertexBuffer> vbo;
  std::unique_ptr<ElementBuffer> ebo;

  std::size_t prevVertArrSize = 0;
  std::size_t prevIndArrSize = 0;

private:
  bool batchStarted = false;

};


#endif //RPG_RENDERER_H

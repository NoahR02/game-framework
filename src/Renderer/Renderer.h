#ifndef RPG_RENDERER_H
#define RPG_RENDERER_H

#include <vector>
#include "../ECS/Components.h"
#include "../ECS/Sprite.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct StaticBatch {

  std::vector<Sprite*> sprites;
  std::vector<float> spriteVertices;
  std::vector<unsigned int> spriteIndices;

  glm::mat4* projectionMatrix;
  ShaderProgram* shaderProgram;
  Texture* texture;

  std::unique_ptr<VertexArray> vertexArray;
  std::unique_ptr<VertexBuffer> vbo;
  std::unique_ptr<ElementBuffer> ebo;

  StaticBatch(glm::mat4& projectionMatrix,
              ShaderProgram& shaderProgram,
              Texture& textureAtlas) {
    vertexArray = std::make_unique<VertexArray>();
    vbo = std::make_unique<VertexBuffer>();
    ebo = std::make_unique<ElementBuffer>();

    this->projectionMatrix = &projectionMatrix;
    this->shaderProgram = &shaderProgram;
    this->texture = &textureAtlas;
  }

  void draw() {
    vertexArray->bind();

    vbo->bind();
    ebo->bind();

    shaderProgram->bind();
    texture->bind();

    shaderProgram->setUniformMatrix4fv("uMVP", 1, false, glm::value_ptr(*projectionMatrix));
    shaderProgram->setUniform1i("uTexture", 0);
    glDrawElements(GL_TRIANGLES, spriteIndices.size(), GL_UNSIGNED_INT, nullptr);
  }

  void uploadToGPU() {
    spriteVertices.clear();
    spriteIndices.clear();

    vertexArray->bind();

    vbo->bind();
    spriteVertices.resize(sprites.size() * 16);
    vbo->fillBuffer(sprites.size() * 16 * sizeof(float), GL_STATIC_DRAW);

    ebo->bind();
    spriteIndices.resize(sprites.size() * 6);
    ebo->fillBuffer(sprites.size() * 6 * sizeof(unsigned int), GL_STATIC_DRAW);

    vertexArray->enableAttribute(0);
    vertexArray->describeAttributeLayout(0, 2, GL_FLOAT, false, sizeof(float) * 4, 0);

    vertexArray->enableAttribute(1);
    vertexArray->describeAttributeLayout(1, 2, GL_FLOAT, false, sizeof(float) * 4, sizeof(float) * 2);


    unsigned int tmp = 0;
    std::size_t i = 0;
    std::size_t j = 0;

    for (const auto& sprite : sprites) {

      float spriteX = sprite->texturePosition.x / (float) texture->width;
      float spriteY = ((float) texture->height - sprite->texturePosition.y) / (float) texture->height;
      float spriteWidth = sprite->texturePosition.width / (float) texture->width;
      float spriteHeight = sprite->texturePosition.height / (float) texture->height;

      glm::vec4 point1 = {sprite->x, sprite->y, 1.0f, 1.0f};
      glm::vec4 point2 = {sprite->x, sprite->y + sprite->height, 1.0f, 1.0f};
      glm::vec4 point3 = {sprite->x + sprite->width, sprite->y, 1.0f, 1.0f};
      glm::vec4 point4 = {sprite->x + sprite->width, sprite->y + sprite->height, 1.0f, 1.0f};

      if (sprite->rotation > 0 || sprite->rotation < 0) {
        glm::mat4 transform(1.0f);


        transform = glm::translate(transform, {sprite->x, sprite->y, 1.0f});
        transform = glm::rotate(transform, glm::radians(sprite->rotation), glm::vec3(0.0f, 0.0f, 1.0f));
        transform = glm::translate(transform, {-sprite->x, -sprite->y, 1.0f});

        point1 = transform * point1;
        point2 = transform * point2;
        point3 = transform * point3;
        point4 = transform * point4;
      }


      //* Vertices *//*                                                                                                      // Texture Coords:
      spriteVertices[ i ] = point1.x;
      spriteVertices[ i + 1 ] = point1.y;
      spriteVertices[ i + 2 ] = spriteX;
      spriteVertices[ i + 3 ] = spriteY;                  // Top left

      spriteVertices[ i + 4 ] = point2.x;
      spriteVertices[ i + 5 ] = point2.y;
      spriteVertices[ i + 6 ] = spriteX;
      spriteVertices[ i + 7 ] = spriteY - spriteHeight;                               // Bottom left

      spriteVertices[ i + 8 ] = point3.x;
      spriteVertices[ i + 9 ] = point3.y;
      spriteVertices[ i + 10 ] = spriteX + spriteWidth;
      spriteVertices[ i + 11 ] = spriteY;      // Top right

      spriteVertices[ i + 12 ] = point4.x;
      spriteVertices[ i + 13 ] = point4.y;
      spriteVertices[ i + 14 ] = spriteX + spriteWidth;
      spriteVertices[ i + 15 ] = spriteY - spriteHeight;                    // Bottom right

      spriteIndices[ j ] = tmp + 0;
      spriteIndices[ j + 1 ] = tmp + 1;
      spriteIndices[ j + 2 ] = tmp + 2;
      spriteIndices[ j + 3 ] = tmp + 2;
      spriteIndices[ j + 4 ] = tmp + 1;
      spriteIndices[ j + 5 ] = tmp + 3;

      i += 16;
      j += 6;
      tmp += 4;
    }

    vbo->fillBufferSubData(spriteVertices, 0);
    ebo->fillBufferSubData(spriteIndices, 0);
  }

  void upload(Sprite& sprite) {
    sprites.push_back(&sprite);
  }

};

struct Renderer {

  void beginDynamicBatch
  (
    glm::mat4& projectionMatrix,
    ShaderProgram& shaderProgram,
    Texture& textureAtlas
  );


  void endDynamicBatch();
  void draw(const Sprite& sprite);
  void draw(StaticBatch& staticBatch);
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

private:
  bool batchStarted = false;

};


#endif //RPG_RENDERER_H

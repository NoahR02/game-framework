#include "Renderer.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <iostream>

void Renderer::draw(const Sprite& sprite) {
  dynamicSprites.emplace_back(&sprite);
}

void Renderer::draw(const Components::TileMap& tilemap) {

}

void Renderer::beginDynamicBatch(glm::mat4& projectionMatrix, ShaderProgram& shaderProgram, Texture& textureAtlas) {
  if(batchStarted) {
    std::cerr << "Batch already started. End the previous batch." << std::endl;
    return;
  }
  batchStarted = true;
  dynamicSprites.clear();
  vertices.clear();
  indices.clear();

  this->projectionMatrix = &projectionMatrix;
  this->shaderProgram = &shaderProgram;
  this->texture = &textureAtlas;
}

void Renderer::endDynamicBatch() {
  if(!batchStarted) {
    std::cerr << "Start a batch before ending one." << std::endl;
    return;
  }
  vertexArray->bind();

  vbo->bind();
  vertices.resize(dynamicSprites.size() * 16);
  vbo->fillBuffer(dynamicSprites.size() * 16 * sizeof(float), GL_DYNAMIC_DRAW);

  ebo->bind();
  indices.resize(dynamicSprites.size() * 6);
  ebo->fillBuffer(dynamicSprites.size() * 6 * sizeof(unsigned int), GL_DYNAMIC_DRAW);

  vertexArray->enableAttribute(0);
  vertexArray->describeAttributeLayout(0, 2, GL_FLOAT, false, sizeof(float) * 4, 0);

  vertexArray->enableAttribute(1);
  vertexArray->describeAttributeLayout(1, 2, GL_FLOAT, false, sizeof(float) * 4, sizeof(float) * 2);


  unsigned int tmp = 0;
  std::size_t i = 0;
  std::size_t j = 0;

  glm::mat4 test(1.0f);

  for(const auto& sprite : dynamicSprites) {

    float spriteX = sprite->texturePosition.x / (float) texture->width;
    float spriteY = ((float) texture->height - sprite->texturePosition.y) / (float) texture->height;
    float spriteWidth = sprite->texturePosition.width / (float) texture->width;
    float spriteHeight = sprite->texturePosition.height / (float) texture->height;

    glm::mat4 transform(1.0f);

    glm::vec4 point1 = {sprite->x, sprite->y, 1.0f, 1.0f};
    glm::vec4 point2 = {sprite->x, sprite->y + sprite->height, 1.0f, 1.0f};
    glm::vec4 point3 = {sprite->x + sprite->width, sprite->y, 1.0f, 1.0f};
    glm::vec4 point4 = {sprite->x + sprite->width, sprite->y + sprite->height, 1.0f, 1.0f};

    if(sprite->rotation > 0.0f || sprite->rotation < 0.0f) {
      std::cout << "Degrees: " << sprite->rotation << std::endl;
      transform = glm::rotate(transform, glm::radians(sprite->rotation), glm::vec3(0.0f, 0.0f, 1.0f));
      /*point1 = transform * point1;
      point2 = transform * point2;
      point3 = transform * point3;
      point4 = transform * point4;*/
    }

    test = transform;


    //* Vertices *//*                                                                                                      // Texture Coords:
    vertices[ i ] = point1.x;
    vertices[ i + 1 ] = point1.y;
    vertices[ i + 2 ] = spriteX;
    vertices[ i + 3 ] = spriteY;                  // Top left

    vertices[ i + 4 ] = point2.x;
    vertices[ i + 5 ] = point2.y;
    vertices[ i + 6 ] = spriteX;
    vertices[ i + 7 ] = spriteY - spriteHeight;                               // Bottom left

    vertices[ i + 8 ] = point3.x;
    vertices[ i + 9 ] = point3.y;
    vertices[ i + 10 ] = spriteX + spriteWidth;
    vertices[ i + 11 ] = spriteY;      // Top right

    vertices[ i + 12 ] = point4.x;
    vertices[ i + 13 ] = point4.y;
    vertices[ i + 14 ] = spriteX + spriteWidth;
    vertices[ i + 15 ] = spriteY - spriteHeight;                    // Bottom right

    indices[ j ] = tmp + 0;
    indices[ j + 1 ] = tmp + 1;
    indices[ j + 2 ] = tmp + 2;
    indices[ j + 3 ] = tmp + 2;
    indices[ j + 4 ] = tmp + 1;
    indices[ j + 5 ] = tmp + 3;

    i += 16;
    j += 6;
    tmp += 4;
  }

  vbo->fillBufferSubData(vertices, 0);
  ebo->fillBufferSubData(indices, 0);

  shaderProgram->bind();
  texture->bind();

  shaderProgram->setUniformMatrix4fv("uMVP", 1, false, glm::value_ptr(*projectionMatrix));
  shaderProgram->setUniformMatrix4fv("test", 1, false, glm::value_ptr(test));
  shaderProgram->setUniform1i("uTexture", 0);

  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);

  batchStarted = false;
}

Renderer::Renderer() {
  vertexArray = std::make_unique<VertexArray>();
  vbo = std::make_unique<VertexBuffer>();
  ebo = std::make_unique<ElementBuffer>();
}
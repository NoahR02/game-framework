#include "Renderer.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

void Renderer::draw(const Sprite& sprite) {
  dynamicSprites.emplace_back(&sprite);
}

void Renderer::draw(const Components::TileMap& tilemap) {

}

void Renderer::beginDynamicBatch(glm::mat4& projectionMatrix, ShaderProgram& shaderProgram, Texture& textureAtlas) {

  dynamicSprites.clear();

/*  vertices.erase(vertices.begin(), vertices.end());
  indices.erase(indices.begin(), indices.end());*/

  this->projectionMatrix = &projectionMatrix;
  this->shaderProgram = &shaderProgram;
  this->texture = &textureAtlas;

}

void Renderer::endDynamicBatch() {
  vertexArray->bind();

  if(dynamicSprites.size()*16* sizeof(float) > prevVertArrSize) {
    vbo->bind();
    vertices.clear();
    vertices.resize(dynamicSprites.size()*16);
    vbo->fillBuffer(static_cast<signed long long int>(dynamicSprites.size()*16 * sizeof(float)), GL_DYNAMIC_DRAW);
    std::cout << "resized arr" << std::endl;

    vertexArray->enableAttribute(0);
    vertexArray->describeAttributeLayout(0, 2, GL_FLOAT, false, sizeof(float ) * 4, 0);

    vertexArray->enableAttribute(1);
    vertexArray->describeAttributeLayout(1, 2, GL_FLOAT, false, sizeof(float ) * 4, sizeof(float) * 2);

  }

  if(dynamicSprites.size()*6*sizeof(unsigned int) > prevIndArrSize) {
    ebo->bind();
    indices.clear();
    indices.resize(dynamicSprites.size()*6);
    ebo->fillBuffer(dynamicSprites.size()*6 * sizeof(unsigned int), GL_DYNAMIC_DRAW);
    std::cout << "resized ind" << std::endl;
  }

  unsigned int tmp = 0;
  std::size_t i = 0;
  std::size_t j = 0;
  for(const auto& sprite : dynamicSprites) {

    //unsigned int tmp = vertices.size()/5;

    float spriteX = (float)sprite->texturePosition.x / (float)texture->width;
    float spriteY = ((float)texture->height-sprite->texturePosition.y) / (float)texture->height;
    float spriteWidth = sprite->texturePosition.width / (float)texture->width;
    float spriteHeight = sprite->texturePosition.height / (float)texture->height;


    //* Vertices *//*                                                                                                      // Texture Coords:
    vertices[i] = sprite->x; vertices[i + 1] = sprite->y; vertices[i + 2] = spriteX; vertices[i + 3] = spriteY+spriteHeight;                  // Top left

    vertices[i + 4] = sprite->x; vertices[i + 5] = sprite->y + sprite->height; vertices[i+6] = spriteX;   vertices[i+7] = spriteY;                               // Bottom left

    vertices[i+8] = sprite->x + sprite->width; vertices[i+9] = sprite->y;                               vertices[i+10] = spriteX+spriteWidth; vertices[i+11] = spriteY+spriteHeight;      // Top right

    vertices[i+12] = sprite->x + sprite->width; vertices[i+13] = sprite->y + sprite->height;              vertices[i+14] = spriteX+spriteWidth; vertices[i+15] = spriteY;                    // Bottom right

    indices[j] = tmp + 0;
    indices[j+1] = tmp + 1;
    indices[j+2] = tmp + 2;
    indices[j+3] = tmp + 2;
    indices[j+4] = tmp + 1;
    indices[j+5] = tmp + 3;

    i+= 16;
    j+= 6;
    tmp += 4;
  }

  vbo->bind();
  ebo->bind();

  prevVertArrSize = vertices.size() * sizeof(float);
  prevIndArrSize = indices.size() * sizeof(unsigned int);

  vbo->fillBufferSubData(vertices, 0);
  ebo->fillBufferSubData(indices, 0);

  shaderProgram->bind();
  texture->bind();

  shaderProgram->setUniformMatrix4fv("uMVP", 1, false, glm::value_ptr(*projectionMatrix));
  shaderProgram->setUniform1i("uTexture", 0);

  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);

}

Renderer::Renderer() {
  vertexArray = std::make_unique<VertexArray>();
  vbo = std::make_unique<VertexBuffer>();
  ebo = std::make_unique<ElementBuffer>();
}
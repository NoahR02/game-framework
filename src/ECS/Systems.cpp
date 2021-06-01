#include "Systems.h"
#include "Components.h"

#include <glad/glad.h>

#include <vector>
#include <iterator>


void Systems::staticRenderGroupSystemDraw(entt::registry& registry, entt::entity entity, entt::entity cameraID) {

  auto& staticRenderGroup = registry.get<Components::StaticRenderGroup>(entity);
  auto& camera = registry.get<Components::Camera>(cameraID);

  staticRenderGroup.vao->bind();
  staticRenderGroup.shaderProgram->bind();
  staticRenderGroup.vbo->bind();
  staticRenderGroup.ebo->bind();
  staticRenderGroup.texture->bind();

  staticRenderGroup.shaderProgram->setUniformMatrix4fv("uMVP", 1, false, &camera.mvp[0][0]);
  staticRenderGroup.shaderProgram->setUniform1i("uTexture", 0);

  if (!staticRenderGroup.indices.empty()) glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(staticRenderGroup.indices.size()), GL_UNSIGNED_INT, nullptr);
}

void Systems::staticRenderGroupSystemUploadData(entt::registry& registry, entt::entity entity, std::vector<float> vertices, std::vector<unsigned int> indices) {

  auto& staticRenderGroup = registry.get<Components::StaticRenderGroup>(entity);

  staticRenderGroup.vao->bind();

  std::copy(vertices.begin(), vertices.end(), std::back_inserter(staticRenderGroup.vertices));
  std::copy(indices.begin(), indices.end(), std::back_inserter(staticRenderGroup.indices));

  staticRenderGroup.vbo->bind();
  staticRenderGroup.vbo->fillBuffer(staticRenderGroup.vertices, GL_STREAM_DRAW);

  staticRenderGroup.ebo->bind();
  staticRenderGroup.ebo->fillBuffer(indices, GL_STREAM_DRAW);

  staticRenderGroup.vao->enableAttribute(0);
  staticRenderGroup.vao->describeAttributeLayout(0, 3, GL_FLOAT, false, sizeof(float) * 5, 0);

  staticRenderGroup.vao->enableAttribute(1);
  staticRenderGroup.vao->describeAttributeLayout(1, 2, GL_FLOAT, false, sizeof(float) * 5, sizeof(float) * 3);
}

void Systems::TileMapAddTile(entt::registry& registry, entt::entity entity, const Tile& tile) {
  auto& tileMap = registry.get<Components::TileMap>(entity);

  for(int i = 0; i < tileMap.tiles.size(); ++i)
    if(tileMap.tiles[i].position.x == tile.position.x && tileMap.tiles[i].position.y == tile.position.y) {

      tileMap.tiles.erase(tileMap.tiles.begin() + i);

      tileMap.tiles.push_back(tile);
      return;
    }

  tileMap.tiles.push_back(tile);
}

void Systems::TileMapUpdate(entt::registry& registry, entt::entity entity) {
  auto& tileMap = registry.get<Components::TileMap>(entity);
  auto& staticRenderGroup = registry.get<Components::StaticRenderGroup>(entity);

  staticRenderGroup.vertices.clear();
  staticRenderGroup.indices.clear();

  staticRenderGroup.vertices.reserve(tileMap.tiles.size() * (5 * 4));
  staticRenderGroup.indices.reserve(tileMap.tiles.size() * 6);

  unsigned int tmp = 0;

  float columns = staticRenderGroup.texture->width / tileMap.tileWidth;
  float rows = staticRenderGroup.texture->height / tileMap.tileHeight;

  for (int i = 0; i < tileMap.tiles.size(); ++i) {
    TexturePosition texPos = tileMap.spriteSheet.getTile(tileMap.tiles[i].tileType);

    texPos.texturePosY = rows - texPos.texturePosY - 1;

    staticRenderGroup.vertices.insert(staticRenderGroup.vertices.end(), { 
      //* Vertices *//*                                                                                                         *//* Texture Coords *//*
      /* top left */     static_cast<float>(tileMap.tiles[i].position.x), static_cast<float>(tileMap.tiles[i].position.y), 0.0f, static_cast<float>(texPos.texturePosX) / columns,
                         static_cast<float>((static_cast<float>(texPos.texturePosY) + 1.0f)) / rows,  // top left
      /* bottom left */  static_cast<float>(tileMap.tiles[i].position.x), static_cast<float>(tileMap.tiles[i].position.y + tileMap.tileHeight), 0.0f, static_cast<float>(texPos.texturePosX) / columns,
                         static_cast<float>(texPos.texturePosY) / rows,  // bottom left
      /* top right */    static_cast<float>(tileMap.tiles[i].position.x + tileMap.tileWidth), static_cast<float>(tileMap.tiles[i].position.y), 0.0f, static_cast<float>((texPos.texturePosX + 1.0f)) / columns,
                         static_cast<float>((static_cast<float>(texPos.texturePosY) + 1.0f)) / rows,  // top right
      /* bottom right */ static_cast<float>(tileMap.tiles[i].position.x + tileMap.tileWidth), static_cast<float>(tileMap.tiles[i].position.y + tileMap.tileHeight), 0.0f, static_cast<float>((texPos.texturePosX + 1.0f)) / columns,
                         static_cast<float>(texPos.texturePosY) / rows  // bottom right
      });

    staticRenderGroup.indices.insert(staticRenderGroup.indices.end(), {
      tmp + 0, tmp + 1, tmp + 2,
      tmp + 2, tmp + 1, tmp + 3
      });


    tmp += 4; // increase vertices
  }

  staticRenderGroup.vao->bind();
  staticRenderGroup.vbo->bind();
  staticRenderGroup.vbo->fillBuffer(staticRenderGroup.vertices, GL_STREAM_DRAW);

  staticRenderGroup.ebo->bind();
  staticRenderGroup.ebo->fillBuffer(staticRenderGroup.indices, GL_STREAM_DRAW);

  staticRenderGroup.vao->enableAttribute(0);
  staticRenderGroup.vao->describeAttributeLayout(0, 3, GL_FLOAT, false, sizeof(float) * 5, 0);

  staticRenderGroup.vao->enableAttribute(1);
  staticRenderGroup.vao->describeAttributeLayout(1, 2, GL_FLOAT, false, sizeof(float) * 5, sizeof(float) * 3);

}

void Systems::cameraMoveLeft(entt::registry& registry, entt::entity entity) {

  auto& camera = registry.get<Components::Camera>(entity);

  camera.view = glm::translate(camera.view, glm::vec3(camera.speed, 0.0f, 0.0f));
  camera.mvp = camera.projection * camera.view;
}

void Systems::cameraMoveRight(entt::registry& registry, entt::entity entity) {

  auto& camera = registry.get<Components::Camera>(entity);

  camera.view = glm::translate(camera.view, glm::vec3(-camera.speed, 0.0f, 0.0f));
  camera.mvp = camera.projection * camera.view;
}

void Systems::cameraMoveUp(entt::registry& registry, entt::entity entity) {

  auto& camera = registry.get<Components::Camera>(entity);

  camera.view = glm::translate(camera.view, glm::vec3(0.0f, camera.speed, 0.0f));
  camera.mvp = camera.projection * camera.view;
}

void Systems::cameraMoveDown(entt::registry& registry, entt::entity entity) {

  auto& camera = registry.get<Components::Camera>(entity);

  camera.view = glm::translate(camera.view, glm::vec3(0.0f, -camera.speed, 0.0f));
  camera.mvp = camera.projection * camera.view;
}

void Systems::cameraZoomIn(entt::registry& registry, entt::entity entity, const int &windowWidth, const int &windowHeight) {

  auto& camera = registry.get<Components::Camera>(entity);

  camera.zoomLevel += 0.01;
  camera.projection = glm::ortho(0.0f, static_cast<float>(windowWidth/camera.zoomLevel), static_cast<float>(windowHeight/camera.zoomLevel),0.0f);
  camera.mvp = camera.projection * camera.view;
}

void Systems::cameraZomOut(entt::registry& registry, entt::entity entity, const int &windowWidth, const int &windowHeight) {

  auto& camera = registry.get<Components::Camera>(entity);

  camera.zoomLevel -= 0.01;
  camera.projection = glm::ortho(0.0f, static_cast<float>(windowWidth/camera.zoomLevel), static_cast<float>(windowHeight/camera.zoomLevel),0.0f);
  camera.mvp = camera.projection * camera.view;
}

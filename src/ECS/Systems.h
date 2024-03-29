#ifndef RPG_SYSTEMS_H
#define RPG_SYSTEMS_H


#include <entt/entt.hpp>
#include <vector>
#include "../TileMap/Tile.h"

#include "Entity.h"

namespace Systems {

  void staticRenderGroupSystemDraw(entt::registry& registry, entt::entity entity, entt::entity cameraID);
  void staticRenderGroupSystemUploadData(entt::registry& registry, entt::entity entity, std::vector<float> vertices, std::vector<unsigned int> indices);

  void TileMapAddTile(entt::registry &registry, entt::entity entity, const Tile& tile);
  void TileMapUpdate(entt::registry &registry, entt::entity entity);

};


#endif //RPG_SYSTEMS_H

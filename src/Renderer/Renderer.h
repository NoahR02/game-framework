#ifndef RPG_RENDERER_H
#define RPG_RENDERER_H

#include <vector>

struct Renderer {

  struct Sprite;
  struct TileMap;

  std::vector<float> staticBatch;
  std::vector<float> dynamicBatch;

  void draw(Sprite sprite);
  void draw(TileMap tilemap);

};


#endif //RPG_RENDERER_H

#include <iostream>
#include <vector>

#include <fstream>
#include <chrono>

#include "cista/containers/vector.h"
#include "cista/reflection/to_tuple.h"
#include <cista/serialization.h>

#include <glad/glad.h>
#include <imgui/imgui.h>

#include "Renderer/VertexArray.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/ShaderProgram.h"
#include "Renderer/Texture.h"
#include "Renderer/ElementBuffer.h"
#include "TileMap/SpriteSheet.h"
#include "Input/Keyboard.h"

#include "Window.h"
#include "GUI/Gui.h"

#include "ECS/Scene.h"
#include "ECS/Components.h"
#include "ECS/Systems.h"

// Todo:
// Abstract entt
//


struct DynamicSprite {
  float x;
  float y;

  float width;
  float height;
};

int main() {
  auto window = std::make_shared<Window>(1600, 900, "RPG");

  auto gui = std::make_unique<Gui>(window);

  std::chrono::duration<std::size_t, std::ratio<1, 144>> refreshRate{1};
  std::cout << std::chrono::duration_cast<std::chrono::microseconds>(refreshRate).count()/1000.0f << "ms" << std::endl;

  Scene scene;

  entt::entity cameraID = scene.registry.create();
  scene.registry.emplace<Components::Camera>(cameraID, window->getWidth(), window->getHeight());

  entt::entity tileMapID = scene.registry.create();
  scene.registry.emplace<Components::TileMap>(tileMapID, 16, 16);
  scene.registry.emplace<Components::StaticRenderGroup>(tileMapID, "assets/tiny-16-basic/basictiles.png");

  auto& tileMap = scene.registry.get<Components::TileMap>(tileMapID);
  auto& camera = scene.registry.get<Components::Camera>(cameraID);

  {
    tileMap.spriteSheet.addTile(TileType::GRASS, TexturePosition{3, 1});
    tileMap.spriteSheet.addTile(TileType::WATER, TexturePosition{5, 3});
    tileMap.spriteSheet.addTile(TileType::LAVA, TexturePosition{2, 8});
    tileMap.spriteSheet.addTile(TileType::WOOD, TexturePosition{0, 2});
    tileMap.spriteSheet.addTile(TileType::DOOR, TexturePosition{0, 6});
    tileMap.spriteSheet.addTile(TileType::TREE, TexturePosition{4, 9});
    tileMap.spriteSheet.addTile(TileType::MOSS_BLOCK, TexturePosition{6, 1});
    tileMap.spriteSheet.addTile(TileType::GOLD_COINS, TexturePosition{4, 8});
    tileMap.spriteSheet.addTile(TileType::SNOW_MOUNTAIN, TexturePosition{7, 7});
    tileMap.spriteSheet.addTile(TileType::DIRT_MOUNTAIN, TexturePosition{6, 7});
  }

  Systems::TileMapAddTile(scene.registry, tileMapID, Tile{{0, 0 }, TileType::GRASS});
  Systems::TileMapAddTile(scene.registry, tileMapID, Tile{{ 16, 16 }, TileType::WATER});

  Systems::TileMapUpdate(scene.registry, tileMapID);

  VertexArray vao;
  VertexBuffer vbo;
  ElementBuffer ebo;

  vbo.bind();
  ebo.bind();

  vbo.fillBuffer(sizeof(float) * 20 * 120000, GL_DYNAMIC_DRAW);
  ebo.fillBuffer(sizeof(float) * 20 * 120000, GL_DYNAMIC_DRAW);

  vao.bind();
  vao.enableAttribute(0);
  vao.describeAttributeLayout(0, 3, GL_FLOAT, false, sizeof(float ) * 5, 0);

  vao.enableAttribute(1);
  vao.describeAttributeLayout(1, 2, GL_FLOAT, false, sizeof(float ) * 5, sizeof(float) * 3);

  ShaderProgram shaderProgram{"shaders/defaultVertex.vert", "shaders/defaultFragment.frag"};
  Texture texture{"assets/tiny-16-basic/dead.png"};


  auto previous = std::chrono::system_clock::now();
  std::chrono::duration<std::size_t, std::ratio<1,10000000>> delta{};


  std::vector<float> vertices = {};

  unsigned int tmp = 0;
  std::vector<unsigned int> indices = {};

  DynamicSprite player{200, 200, 256, 256};

  for(int i = 0; i < 100'000; ++i) {

    player.x += 16;
    player.y += 16;
    vertices.insert(vertices.end(), {
      /* top left */      player.x, player.y, 0.0f,                                       0.0f, 1.0f,
      /* bottom left */   player.x, player.y + player.height, 0.0f,                       0.0f, 0.0f,
      /* top right */     player.x + player.width, player.y, 0.0f,                        1.0f, 1.0f,
      /* bottom right */  player.x + player.width, player.y + player.height, 0.0f,        1.0f, 0.0f
    });

    indices.insert(indices.end(), {
      tmp + 0, tmp + 1, tmp + 2,
      tmp + 2, tmp + 1, tmp + 3
    });

    tmp += 4;

  }

  while(!window->shouldWindowClose()) {
    const auto now = std::chrono::system_clock::now();
    delta = now-previous;

    if(delta >= refreshRate) {
      previous = now;
      if (keys[GLFW_KEY_W]) Systems::cameraMoveUp(scene.registry, cameraID);
      if (keys[GLFW_KEY_A]) Systems::cameraMoveLeft(scene.registry, cameraID);
      if (keys[GLFW_KEY_S]) Systems::cameraMoveDown(scene.registry, cameraID);
      if (keys[GLFW_KEY_D]) Systems::cameraMoveRight(scene.registry, cameraID);

      if (keys[GLFW_KEY_EQUAL]) Systems::cameraZoomIn(scene.registry, cameraID, window->getWidth(), window->getHeight());
      if (keys[GLFW_KEY_MINUS])Systems::cameraZomOut(scene.registry, cameraID, window->getWidth(), window->getHeight());
    }

    gui->captureViewport();
    window->setBackgroundColor(0.3f* 255, 0.5f* 25, 0.7f * 255, 1.0f);

    Systems::staticRenderGroupSystemDraw(scene.registry, tileMapID, cameraID);

    vao.bind();

    vbo.bind();
    ebo.bind();

    vbo.fillBufferSubData(vertices, 0);
    ebo.fillBufferSubData(indices, 0);

    shaderProgram.bind();
    texture.bind();

    shaderProgram.setUniformMatrix4fv("uMVP", 1, false, &camera.mvp[0][0]);
    shaderProgram.setUniform1i("uTexture", 0);


    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);


    // Unbind capture of GUI viewport capture...
      glBindFramebuffer(GL_FRAMEBUFFER, 0);
      gui->render(scene.registry, tileMapID, cameraID);

      window->swapBuffers();
      window->pollEvents();

  }


  return 0;
}
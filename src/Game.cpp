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
#include "SpriteSheet.h"
#include "TileMap/TileMap.h"
#include "Input/Keyboard.h"

#include "Window.h"
#include "GUI/Gui.h"
#include "TileMap/Grid.h"

int main() {
  auto window = std::make_shared<Window>(1600, 900, "RPG");
  auto camera = std::make_unique<Camera>(window->getWidth(), window->getHeight());

  SpriteSheet spriteSheet;
  spriteSheet.addTile(TileType::GRASS, TexturePosition{3, 1});
  spriteSheet.addTile(TileType::WATER, TexturePosition{5, 3});
  spriteSheet.addTile(TileType::LAVA, TexturePosition{2, 8});
  spriteSheet.addTile(TileType::WOOD, TexturePosition{0, 2});
  spriteSheet.addTile(TileType::DOOR, TexturePosition{0, 6});
  spriteSheet.addTile(TileType::TREE, TexturePosition{4, 9});
  spriteSheet.addTile(TileType::MOSS_BLOCK, TexturePosition{6, 1});
  spriteSheet.addTile(TileType::GOLD_COINS, TexturePosition{4, 8});
  spriteSheet.addTile(TileType::SNOW_MOUNTAIN, TexturePosition{7, 7});
  spriteSheet.addTile(TileType::DIRT_MOUNTAIN, TexturePosition{6, 7});

  TileMap tileMap(spriteSheet);

  // Deserialize Data
  std::ifstream readFile("writeFile.txt", std::ios::binary);
  std::vector<unsigned char> contents((std::istreambuf_iterator<char>(readFile)), std::istreambuf_iterator<char>());
  readFile.close();

  auto loadedTiles = cista::deserialize<cista::basic_vector<Tile>>(contents);
  std::copy(loadedTiles->begin(), loadedTiles->end(), std::back_inserter(tileMap.tiles));
  tileMap.upload();


  tileMap.addTile({{-200, 0}, TileType::LAVA});
  tileMap.upload();

  auto gui = std::make_unique<Gui>(window);
  auto grid = std::make_unique<Grid>(window->getWidth(), window->getHeight(), 16, 16);

  std::chrono::duration<std::size_t, std::ratio<1, 144>> refreshRate{1};
  std::cout << std::chrono::duration_cast<std::chrono::microseconds>(refreshRate).count()/1000.0f << "ms" << std::endl;

  auto previous = std::chrono::system_clock::now();
  std::chrono::duration<std::size_t, std::ratio<1,10000000>> delta{};

  while(!window->shouldWindowClose()) {
    const auto now = std::chrono::system_clock::now();
    delta = now-previous;

    if(delta >= refreshRate) {
      previous = now;
      if (keys[GLFW_KEY_W]) camera->moveUp();
      if (keys[GLFW_KEY_A]) camera->moveLeft();
      if (keys[GLFW_KEY_S]) camera->moveDown();
      if (keys[GLFW_KEY_D]) camera->moveRight();

      if (keys[GLFW_KEY_EQUAL]) camera->zoomIn(window->getWidth(), window->getHeight());
      if (keys[GLFW_KEY_MINUS]) camera->zoomOut(window->getWidth(), window->getHeight());
    }
      gui->captureViewport();
      window->setBackgroundColor(0.3f* 255, 0.5f* 25, 0.7f * 255, 1.0f);

    // Draw the tilemap
      tileMap.draw(*camera);
      grid->draw(*camera);
    // Unbind capture of GUI viewport capture...
      glBindFramebuffer(GL_FRAMEBUFFER, 0);
      gui->render(tileMap, *camera);

      window->swapBuffers();
      window->pollEvents();

  }

  // Serialize Data
  {
    std::vector<unsigned char> buf = cista::serialize(tileMap.tiles);
    std::ofstream writeFile("writeFile.txt", std::ios::out | std::ios::binary);
    size_t tmp = buf.size();
    writeFile.write((char*)buf.data(), tmp);
    writeFile.close();
  }

  return 0;
}
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Engine/Window.h"
#include "Engine/GameObjects/SpriteSheet.h"
#include "Engine/GameObjects/GameObject.h"
#include "Engine/GameObjects/Player.h"
#include "Game.h"
#include "Engine/Events/Keyboard.h"
#include "Engine/Renderer/Renderer.h"
#include "Engine/LevelEditor/LevelEditor.h"

#include <filesystem>

Game::Game() {
  window = new Window(1600, 900, "RPG");
  window->enableVsync(true);
  renderer = new Renderer();

  if(!std::filesystem::exists(assetsPath)) assetsPath = std::filesystem::current_path().parent_path().append("assets");
}

void Game::start() {

  basicTiles = new SpriteSheet(assetsPath.generic_string() + "/tiny-16-basic/basictiles.png");
  characters = new SpriteSheet(assetsPath.generic_string() + "/tiny-16-basic/characters.png");

  grassTexture = basicTiles->getSprite(16, 16, 3, 1);
  grass = new GameObject(grassTexture, 0, 700, window->getWidth(), 700);

  princessTexture = characters->getSprite(16, 16, 7, 3);
  princess = new Player(princessTexture, window->getWidth() / 2 - (64), window->getHeight()/2 +(64), 64*2, 64*2);
  princess->setProgram(vertexShaderSource, fragmentShaderSource);

  ghostTexture = characters->getSprite(16, 16, 8, 4);
  ghost = new GameObject(ghostTexture, 800, 500, 64 * 2, 64 * 2);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  frameBuffer = new FrameBuffer(*window);
  levelEditor = new LevelEditor(*window, *frameBuffer);

  while(!glfwWindowShouldClose(window->glfwWindow)) {
    update();
    render();
  }

}

void Game::update() {
  if(Keyboard::keys[GLFW_KEY_W]) {
    princess->texture = characters->getSprite(16, 16, 8, 3);
    renderer->camera->moveDown();
  }

  if(Keyboard::keys[GLFW_KEY_A]) {
    princess->texture = characters->getSprite(16, 16, 8, 1);
    renderer->camera->moveRight();
  }

  if(Keyboard::keys[GLFW_KEY_S]) {;
    princess->texture = characters->getSprite(16, 16, 8, 0);
    renderer->camera->moveUp();
  }

  if(Keyboard::keys[GLFW_KEY_D]) {
    princess->texture = characters->getSprite(16, 16, 7, 2);
    renderer->camera->moveLeft();
  }
}

void Game::render() {
  renderer->clear();

  frameBuffer->bind();
  frameBuffer->frameBufferTexture.bind();
  glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  renderer->draw(*grass);
  renderer->draw(*ghost);
  renderer->draw(*princess);
  frameBuffer->unBind();
  frameBuffer->frameBufferTexture.unbind();

  levelEditor->render();


  renderer->swapBuffersAndPollEvents(window->glfwWindow);
}

Game::~Game() {
  // Delete SpriteSheets
  delete basicTiles;
  delete characters;

  // Delete Textures
  delete princessTexture;
  delete ghostTexture;
  delete grassTexture;

  // Delete GameObjects
  delete ghost;
  delete princess;
  delete grass;

  // Delete Level Editor
  delete levelEditor;

  // Delete Framebuffer
  delete frameBuffer;

  // Delete Renderer and Window.
  delete renderer;
  delete window;
}

int main() {
  Game* game = new Game();
  game->start();
  delete game;

  return 0;
}
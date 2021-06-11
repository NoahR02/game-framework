#ifndef RPG_ENGINE_H
#define RPG_ENGINE_H

#include <memory>
#include "events/Observer.h"
#include "events/Subject.h"

struct Engine {

  Engine();

  std::shared_ptr<Window> window;
  std::unique_ptr<Gui> gui;
  std::unique_ptr<Renderer> renderer;

  std::shared_ptr<ShaderProgram> shaderProgram;
  std::shared_ptr<Texture> texture;

  std::vector<Sprite> sprites;

  void update(float& deltaTime);
  void render();
  void start();

  float refreshRate = 1.0f / 144.0f;
  float delta = 0.0f;

  Scene* currentScene;

protected:
  float previous;

};
#endif //RPG_ENGINE_H

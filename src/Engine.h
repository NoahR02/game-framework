#ifndef RPG_ENGINE_H
#define RPG_ENGINE_H

#include <memory>
#include <AL/alc.h>

#include "Window.h"
#include "GUI/Gui.h"
#include "Renderer/Renderer.h"
#include "ECS/Scene.h"


struct Engine {

  Engine();

  std::shared_ptr<Window> window;
  std::unique_ptr<Gui> gui;
  std::unique_ptr<Renderer> renderer;

  std::shared_ptr<ShaderProgram> shaderProgram;
  std::shared_ptr<Texture> texture;

  std::vector<Sprite> sprites;

  ALCdevice* device;
  ALCcontext* context;

  void updatePhysics(float& deltaTime);

  float timeStep = 1.0f / 60.0f;
  float delta = 0.0f;

  Scene* currentScene;

  ~Engine();

  float previous;

};
#endif //RPG_ENGINE_H

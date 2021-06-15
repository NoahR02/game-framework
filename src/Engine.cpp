#include <iostream>

#include <fstream>
#include <chrono>

#include <glad/glad.h>
#include <box2d/box2d.h>

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
#include "ECS/Entity.h"

#include "ECS/Systems.h"
#include "ECS/Sprite.h"
#include "Renderer/Renderer.h"
#include "Engine.h"

#include "AL/al.h"
#include "AL/alc.h"
#include "Audio/AudioFile.h"
#include "Audio/AudioSource.h"
#include "game/Player.h"
#include "ECS/Camera.h"

// TODO: Move keyboard input out of loop.
// TODO: Add scripting
// TODO: Add physics.
// TODO: Add sound.
// TODO: Add cmake code to move openal dll next to the exe

void Engine::update(float &deltaTime) {
  const auto now = (float) glfwGetTime();
  deltaTime = now - previous;
  if(deltaTime >= timeStep) {
    previous = now;

    currentScene->world.world->Step(timeStep, 8, 3);

    for(auto* entity : currentScene->entities) {
      entity->update(delta);
    }
  }
}

void Engine::render() {
  for(auto* entity : currentScene->entities) {
    entity->render(delta);
  }

  //gui->captureViewport();
  window->setBackgroundColor(0.0f, 0.0f, 0.0f, 1.0f);

  auto &camera = currentScene->currentCamera->getComponent<Camera>();

  renderer->beginDynamicBatch(camera.mvp, *shaderProgram, *texture);

  //for(const auto& sprite : sprites) renderer->draw(sprite);
  auto view = currentScene->registry.view<Sprite>();
  for(auto entityID : view) {
    auto &sprite = currentScene->registry.get<Sprite>(entityID);
    renderer->draw(sprite);
  }


  renderer->endDynamicBatch();


  // Unbind capture of GUI viewport capture...
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  // gui->render(scene.registry, tileMapID, cameraID);

  window->swapBuffers();
  window->pollEvents();
}

Engine::Engine() {
  window = std::make_shared<Window>(1600, 900, "RPG");
  renderer = std::make_unique<Renderer>();

  shaderProgram = std::make_unique<ShaderProgram>("shaders/defaultVertex.vert", "shaders/defaultFragment.frag");
  texture = std::make_unique<Texture>("assets/tiny-16-basic/basictiles.png");

  device = alcOpenDevice(nullptr);
  if(!device) {
    std::cerr << "Could not get audio device." << std::endl;
    return;
  } else {
    std::cout << "Found audio device." << std::endl;
  }

  context = alcCreateContext(device, nullptr);

  if(alcMakeContextCurrent(context)) {
    std::cout << "Made OpenAL context current." << std::endl;
  } else {
    std::cerr << "Failed to make OpenAL context current." << std::endl;
  }
}

Engine::~Engine() {
  alcDestroyContext(context);
  alcCloseDevice(device);
}

void Engine::start() {
}
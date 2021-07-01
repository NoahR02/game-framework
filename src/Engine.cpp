#include <iostream>
#include <fstream>

#include "Renderer/VertexArray.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/ShaderProgram.h"
#include "Renderer/Texture.h"
#include "Renderer/ElementBuffer.h"
#include "TileMap/SpriteSheet.h"

#include "Window.h"
#include "ECS/Scene.h"
#include "ECS/Systems.h"
#include "ECS/Sprite.h"
#include "Renderer/Renderer.h"
#include "Engine.h"

#include "AL/alc.h"

void Engine::updatePhysics(float &deltaTime) {
  const auto now = (float) glfwGetTime();
  deltaTime = now - previous;
  if(deltaTime >= timeStep) {
    previous = now;

    currentScene->world.step(deltaTime);

    for(auto* entity : currentScene->entities) {
      entity->update(delta);
    }

    auto view = currentScene->registry.view<Body, Sprite>();
    for(auto entityID : view) {
      auto &sprite = currentScene->registry.get<Sprite>(entityID);
      auto &body = currentScene->registry.get<Body>(entityID);
      auto physicsPos = body.getPosition( );
      sprite.x = physicsPos.x - sprite.width / 2;
      sprite.y = physicsPos.y - sprite.height;
    }

  }
}

Engine::Engine() {
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
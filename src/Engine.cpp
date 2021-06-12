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
#include "Sprite.h"
#include "Renderer/Renderer.h"
#include "Engine.h"

#include "AL/al.h"
#include "AL/alc.h"
#include "AudioFile.h"
#include "AudioSource.h"
#include "Player.h"

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

    auto view = currentScene->registry.view<Components::Camera, Components::Controller, Sprite, AudioSource>();
    /*for(auto entityID : view) {
      Entity cameraController {entityID, this->currentScene};
      auto &controller = currentScene->registry.get<Components::Controller>(entityID);
      auto &sprite = currentScene->registry.get<Sprite>(entityID);
      auto &camera = currentScene->registry.get<Components::Camera>(entityID);
      auto &audioSrc = currentScene->registry.get<AudioSource>(entityID);

      if(controller.active) {
        if(keys[GLFW_KEY_W]) {
          Systems::cameraMoveUp(cameraController);
          sprite.y -= camera.speed;
        }
        if(keys[GLFW_KEY_A]) {
          Systems::cameraMoveLeft(cameraController);
          sprite.x -= camera.speed;
        }
        if(keys[GLFW_KEY_S]) {
          Systems::cameraMoveDown(cameraController);
          sprite.y += camera.speed;
        }
        if(keys[GLFW_KEY_D]) {
          Systems::cameraMoveRight(cameraController);
          sprite.x += camera.speed;
        }

        if(keys[GLFW_KEY_EQUAL])
          Systems::cameraZoomIn(cameraController);
        if(keys[GLFW_KEY_MINUS])
          Systems::cameraZomOut(cameraController);
      }
    }*/
  }
}

void Engine::render() {
  //gui->captureViewport();
  window->setBackgroundColor(0.3f * 255, 0.5f * 25, 0.7f * 255, 1.0f);

  auto &camera = currentScene->currentCamera->getComponent<Components::Camera>();

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

int main() {
  Engine engine;
  Scene scene;

  engine.currentScene = &scene;

  auto bounce = std::make_shared<AudioFile>("assets/sounds/bounce.wav");
  auto dungeonMusic = std::make_shared<AudioFile>("assets/sounds/jrpg-dungeon-loop.wav");

 /* // Editor Camera
  auto defaultCameraID = engine.currentScene->createEntity();
  auto &defaultCamera = defaultCameraID.addComponent<Components::Camera>(engine.window->getWidth(),
                                                                         engine.window->getHeight());
  scene.currentCamera = &defaultCameraID;*/

  auto player = engine.currentScene->createEntitySubClass<Player>();
  player.getComponent<Components::Camera>().setWidth(engine.window->getWidth());
  player.getComponent<Components::Camera>().setHeight(engine.window->getHeight());
  scene.currentCamera = &player;

  //engine.window->addObserver(&defaultCamera);
  engine.window->addObserver(&player.getComponent<Components::Camera>());

  auto &audioSrc = player.addComponent<AudioSource>(bounce);
  setAudioFile(player, dungeonMusic);
  play(player);


  b2Vec2 gravity {0.0f, -10.0f};
  b2World world(gravity);
  b2BodyDef groundBodyDef;
  groundBodyDef.position.Set(0.0f, -10.0f);
  b2Body* groundBody = world.CreateBody(&groundBodyDef);
  b2PolygonShape groundBox;
  groundBox.SetAsBox(50, 10);
  groundBody->CreateFixture(&groundBox, 0);

  b2BodyDef dynamicBodyDef;
  dynamicBodyDef.type = b2_dynamicBody;
  dynamicBodyDef.position.Set(0.0f, 4.0f);
  b2Body* dynamicBody = world.CreateBody(&dynamicBodyDef);
  b2PolygonShape dynamicBodyShape;
  dynamicBodyShape.SetAsBox(1.0f, 1.0f);
  b2FixtureDef dynamicFixtureDef;
  dynamicFixtureDef.shape = &dynamicBodyShape;
  dynamicFixtureDef.density = 1.0f;
  dynamicFixtureDef.density = 0.3f;
  dynamicBody->CreateFixture(&dynamicFixtureDef);

  float timeStep = engine.timeStep;
  int32 velocityIterations = 8;
  int32 positionIterations = 3;

/*  int i = 0;
  while(1) {
    ++i;
    world.Step(timeStep, velocityIterations, positionIterations);
    std::cout << std::format("Dynamic Body Pos({}, {})", dynamicBody->GetPosition().x, dynamicBody->GetPosition().y) << std::endl;
    if(i >= 60*2000)
      return 0;
  }*/

  engine.start();
}

Engine::Engine() {
  window = std::make_shared<Window>(1600, 900, "RPG");
  renderer = std::make_unique<Renderer>();

  shaderProgram = std::make_unique<ShaderProgram>("shaders/defaultVertex.vert", "shaders/defaultFragment.frag");
  texture = std::make_unique<Texture>("assets/tiny-16-basic/dead.png");

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

  float scale = 4;
  for(float x = 0; x < 2; ++x) {
    for(float y = 0; y < 2; ++y) {
      auto spriteID = currentScene->createEntity();
      spriteID.addComponent<Sprite>(x * 16 * scale, y * 16 * scale, 16 * scale, 16 * scale,
                                    TextureRectangle {0, 32, 16, 16}, Color {1.0f, 1.0f, 1.0f, 1.0f});
    }
  }

  previous = (float) glfwGetTime();

  while(!window->shouldWindowClose()) {
    update(delta);
    render();
  }


}
#include "../Engine.h"

#include "AL/al.h"
#include <box2d/box2d.h>

#include "../ECS/Components.h"
#include "Player.h"
#include "../Audio/AudioSource.h"
#include "../ECS/Sprite.h"
#include "../ECS/Camera.h"
#include "../ECS/Body.h"

#include <fstream>

int main() {
  Engine engine;
  Scene scene;

  scene.world.setScaleX(16);
  scene.world.setScaleY(16);

  engine.currentScene = &scene;

  auto player = engine.currentScene->createEntitySubClass<Player>();

  auto& playerCamera = player.getComponent<Camera>();
  playerCamera.setWidth(engine.window->getViewportWidth());
  playerCamera.setHeight(engine.window->getViewportHeight());
  cameraRecalculate(player);

  auto& playerBody = player.addBody(glm::vec2(0, 0));
  playerBody.setType(Body::BodyType::DYNAMIC_BODY);

  player.setX(0);
  player.setY(0);

  scene.currentCamera = &player;
  engine.window->addObserver(&playerCamera);

  auto dungeonMusic = std::make_shared<AudioFile>("assets/sounds/jrpg-dungeon-loop.wav");

  auto &audioSrc = player.addComponent<AudioSource>(dungeonMusic);
  play(player);

  float scale = 4;
  for(float x = 0; x < 2; ++x) {
    for(float y = 0; y < 2; ++y) {
      auto spriteID = engine.currentScene->createEntity();
      spriteID.addComponent<Sprite>(x * 16 * scale, y * 16 * scale, 16 * scale, 16 * scale,
                                    TextureRectangle {0, 32, 16, 16}, Color {1.0f, 1.0f, 1.0f, 1.0f});
    }
  }


  auto platform = engine.currentScene->createEntity();
  Sprite& platformSprite = platform.addComponent<Sprite>(0.0f, 450.0f, 16 * 500 * scale, 16 * scale,
                                TextureRectangle {0, 32, 16, 16}, Color {1.0f, 1.0f, 1.0f, 1.0f});

  Body& platformBody = platform.addBody(glm::vec2(platformSprite.x, platformSprite.y));
  platformBody.setType(Body::BodyType::STATIC_BODY);

  auto whiteSquare = engine.currentScene->createEntity();
  whiteSquare.addComponent<Sprite>(0.0f, 0.0f,
                                   engine.window->getViewportWidth(), engine.window->getViewportHeight(),
                                   TextureRectangle {0 , 0, 16, 16},
                                   Color {1.0f, 1.0f, 1.0f, 0.0f}
  );


  engine.previous = (float) glfwGetTime();

  int32 velocityIterations = 8;
  int32 positionIterations = 3;

  while(!engine.window->shouldWindowClose()) {
    engine.update(engine.delta);

    auto playerPhysicsPos = playerBody.getPosition();
    player.setX(playerPhysicsPos.x);
    player.setY(playerPhysicsPos.y);


    auto platformPhysicsPos = platformBody.getPosition();
    platformSprite.x = platformPhysicsPos.x;
    platformSprite.y = platformPhysicsPos.y;

    auto& camera = engine.currentScene->currentCamera->getComponent<Camera>();
    whiteSquare.getComponent<Sprite>().width = engine.window->getViewportWidth() / (engine.window->getViewportWidth() / 1600);
    whiteSquare.getComponent<Sprite>().height = engine.window->getViewportHeight() / (engine.window->getViewportHeight() / 900);

    engine.render();
  }

}

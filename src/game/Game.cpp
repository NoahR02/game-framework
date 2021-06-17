#include "../Engine.h"

#include <box2d/box2d.h>

#include "Player.h"
#include "../Audio/AudioSource.h"
#include "../ECS/Camera.h"

int main() {
  Engine engine;
  Scene scene;

  engine.currentScene = &scene;

  auto player = engine.currentScene->createEntitySubClass<Player>();

  auto& playerCamera = player.getComponent<Camera>();
  playerCamera.setWidth(engine.window->getViewportWidth());
  playerCamera.setHeight(engine.window->getViewportHeight());
  cameraRecalculate(player);


  player.getComponent<Body>().setPosition({12 * 16, 0.0f});
  std::variant<PolygonShape, CircleShape, EdgeShape, ChainShape> shape = PolygonShape{16, 16};
  player.getComponent<Body>().addCollisionShape(shape);

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
      spriteID.addBody({x * 16 * scale, y * 16 * scale});
    }
  }


  auto platform = engine.currentScene->createEntity();
  Sprite& platformSprite = platform.addComponent<Sprite>(0.0f, 450.0f, 16 * 10 * scale, 16 * scale,
                                TextureRectangle {0, 32, 16, 16}, Color {1.0f, 1.0f, 1.0f, 1.0f});
  std::variant<PolygonShape, CircleShape, EdgeShape, ChainShape> shape2 = PolygonShape{16, 16};

  Body& platformBody = platform.addBody(glm::vec2(platformSprite.x, platformSprite.y));

  platformBody.addCollisionShape(shape2);
  platformBody.setPosition({12 * 16, 0.0f});
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

    auto& camera = engine.currentScene->currentCamera->getComponent<Camera>();
    whiteSquare.getComponent<Sprite>().width = engine.window->getViewportWidth() / (engine.window->getViewportWidth() / 1600);
    whiteSquare.getComponent<Sprite>().height = engine.window->getViewportHeight() / (engine.window->getViewportHeight() / 900);

    engine.render();
  }

}

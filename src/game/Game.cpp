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
  std::variant<PolygonShape, CircleShape, EdgeShape, ChainShape> shape = PolygonShape{};
  PolygonShape& playerShape = std::get<PolygonShape>(shape);
  Sprite& playerSprite = player.getComponent<Sprite>();
  playerShape.world = &engine.currentScene->world;
  playerShape.setAsBox(glm::vec2{playerSprite.width, playerSprite.height});
  player.getComponent<Body>().addCollisionShape(shape);
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
                                    TextureRectangle {0, 16, 16, 16}, Color {1.0f, 1.0f, 1.0f, 1.0f});
      spriteID.addBody({x * 16 * scale, y * 16 * scale});
    }
  }


  auto platform = engine.currentScene->createEntity();
  Sprite& platformSprite = platform.addComponent<Sprite>(0.0f, 450.0f, 16 * scale, 16 * scale,
                                TextureRectangle {0, 32, 16, 16}, Color {1.0f, 1.0f, 1.0f, 1.0f});
  std::variant<PolygonShape, CircleShape, EdgeShape, ChainShape> shape2 = PolygonShape{};

  Body& platformBody = platform.addBody(glm::vec2(platformSprite.x, platformSprite.y));
  platformBody.setPosition({platformSprite.x + platformSprite.width/2, platformSprite.y + platformSprite.height/2});
  PolygonShape& platformShape = std::get<PolygonShape>(shape2);
  platformShape.world = &engine.currentScene->world;
  platformShape.setAsBox({platformSprite.width, platformSprite.height});
  platformBody.addCollisionShape(shape2);


  auto whiteSquare = engine.currentScene->createEntity();
  whiteSquare.addComponent<Sprite>(0.0f, 0.0f,
                                   engine.window->getViewportWidth(), engine.window->getViewportHeight(),
                                   TextureRectangle {0 , 0, 16, 16},
                                   Color {1.0f, 1.0f, 1.0f, 1.0f}
  );


  engine.previous = (float) glfwGetTime();

  while(!engine.window->shouldWindowClose()) {
    engine.update(engine.delta);

    auto& camera = engine.currentScene->currentCamera->getComponent<Camera>();
    whiteSquare.getComponent<Sprite>().width = engine.window->getViewportWidth() / (engine.window->getViewportWidth() / 1600);
    whiteSquare.getComponent<Sprite>().height = engine.window->getViewportHeight() / (engine.window->getViewportHeight() / 900);

    engine.render();
  }

}
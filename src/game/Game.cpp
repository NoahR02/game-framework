#include "../Engine.h"
#include "Player.h"
#include "../ECS/Camera.h"

// TODO:
//  Move game assets from engine into game.

int main() {
  auto window = std::make_shared<Window>(1600, 900, "RPG");
  Engine engine;
  engine.window = window;

  Scene scene;
  engine.currentScene = &scene;

  auto defaultCameraID = engine.currentScene->createEntity();
  auto& defaultCamera = defaultCameraID.addComponent<Camera>(engine.window->getViewportWidth(), engine.window->getViewportHeight());
  engine.currentScene->currentCamera = &defaultCameraID;

  // Set gravity to 0 because it is a RPG.
  scene.world.setGravity(glm::vec2{0.0f, 0.0f});

  auto square = engine.currentScene->createEntity();
  auto& squareSprite = square.addComponent<Sprite>();

  squareSprite.x = 0, squareSprite.y = 0;
  squareSprite.width = 64, squareSprite.height = 64;
  squareSprite.texturePosition = {48, 48, 16, 16};

  auto bg = engine.currentScene->createEntity();
  auto& bgSprite = bg.addComponent<Sprite>();

  bgSprite.x = 0, bgSprite.y = 0;
  bgSprite.width = 1600, bgSprite.height = 900;
  bgSprite.texturePosition = {16, 16, 16, 16};

  auto player = engine.currentScene->createEntitySubClass<Player>();

  auto& playerCamera = player.getComponent<Camera>();
  playerCamera.setWidth(engine.window->getViewportWidth());
  playerCamera.setHeight(engine.window->getViewportHeight());

  #define Shape std::variant<PolygonShape, CircleShape, EdgeShape, ChainShape>
  Shape shape = PolygonShape{};

  auto& playerShape = std::get<PolygonShape>(shape);
  auto& playerSprite = player.getComponent<Sprite>();

  playerShape.setAsBox(engine.currentScene->world, glm::vec2{playerSprite.width, playerSprite.height});
  player.getComponent<Body>().addCollisionShape(shape);

  //scene.currentCamera = &player;
  engine.window->addObserver(&playerCamera);

  engine.previous = (float)glfwGetTime();

  while(!engine.window->shouldWindowClose()) {
    engine.window->clear(255.0f, 255.0f, 255.0f, 1.0f);
   // engine.updatePhysics(engine.delta);

    auto &camera = engine.currentScene->currentCamera->getComponent<Camera>();

    engine.renderer->beginDynamicBatch(camera.mvp, *engine.shaderProgram, *engine.texture);
    {
      engine.renderer->draw(bgSprite);
      engine.renderer->draw(playerSprite);
      engine.renderer->draw(squareSprite);
    }
    engine.renderer->endDynamicBatch();

    engine.window->swapBuffers();
    engine.window->pollEvents();
  }

}

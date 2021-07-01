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

  // Set gravity to 0 because it is a RPG.
  scene.world.setGravity(glm::vec2{0.0f, 0.0f});

  auto square = engine.currentScene->createEntity();
  auto& squareSprite = square.addComponent<Sprite>();

  squareSprite.x = 16;
  squareSprite.y = 16;
  squareSprite.width = 16;
  squareSprite.height = 16;
  squareSprite.texturePosition = {0, 0, 16, 16};

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

  scene.currentCamera = &player;
  engine.window->addObserver(&playerCamera);

  engine.previous = (float)glfwGetTime();

  while(!engine.window->shouldWindowClose()) {
    engine.window->setBackgroundColor(0.0f, 0.0f, 0.0f, 1.0f);

    engine.updatePhysics(engine.delta);

    auto &camera = engine.currentScene->currentCamera->getComponent<Camera>();

    engine.renderer->beginDynamicBatch(camera.mvp, *engine.shaderProgram, *engine.texture);
    {
      engine.renderer->draw(playerSprite);
      engine.renderer->draw(squareSprite);
    }
    engine.renderer->endDynamicBatch();

    engine.window->swapBuffers();
    engine.window->pollEvents();
  }

}

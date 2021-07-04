#include "../Engine.h"
#include "../ECS/Camera.h"

#include "../Input/Keyboard.h"
#include <sstream>

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

  auto player = engine.currentScene->createEntity();
  auto& playerSprite = player.addComponent<Sprite>();

  /*playerSprite.construct(200, 200,
                         64, 64,
                         {16*8, 48, 16, 16}, {});*/

  const char* map = "assets/tiny-16-basic/basictiles.png\n"
                    "TTTTTTTTTTTTTTT\n"
                    "WWWWWGGGGGGGGGT\n"
                    "WWWWWGGGGGGGGGT\n"
                    "WWWWWGGGGGGGGGT\n"
                    "TGGGGGGGGGGGGGT\n"
                    "TGGGGGGGGGGGGGT\n"
                    "TGGGGGGGGGGGGGT\n"
                    "TGGGGGGGGGGGGGT\n"
                    "TGGGGGGGGGGGGGT\n"
                    "TTTTTTTTTTTTTTT\n";

  std::string line;
  std::istringstream tmpMap(map);
  std::getline(tmpMap, line);

  std::shared_ptr<Texture> texture;

  if(line.empty()) {
    std::cerr << "No file to use." << std::endl;
    texture = engine.texture;
  } else {
    texture = std::make_shared<Texture>(line);
    int tilePositionX = 0;
    int tilePositionY = 0;
    int scale = 5;
    while(std::getline(tmpMap, line)) {

      for(int i = 0; i < line.size(); ++i) {
        switch(line[i]) {
          case 'G': {
            auto tile = scene.createEntity();
            auto& tileSprite = tile.addComponent<Sprite>();
            tileSprite.construct(tilePositionX  * scale, tilePositionY  * scale, 16 * scale, 16 * scale,
                                   {16*3, 16 * 1, 16, 16},{});
            break;
          }

          case 'T': {

            auto tile = scene.createEntity();
            auto& tileSprite = tile.addComponent<Sprite>();
            tileSprite.construct(tilePositionX  * scale, tilePositionY  * scale, 16 * scale, 16 * scale,
                                 {16*4, 16 * 9, 16, 16},{});

            auto grass = scene.createEntity();
            auto& grassSprite = grass.addComponent<Sprite>();
            grassSprite.construct(tilePositionX  * scale, tilePositionY  * scale, 16 * scale, 16 * scale,
                                  {16*3, 16 * 1, 16, 16},{});
            break;
          }

          case 'W': {
            auto tile = scene.createEntity();
            auto& tileSprite = tile.addComponent<Sprite>();
            tileSprite.construct(tilePositionX  * scale, tilePositionY  * scale, 16 * scale, 16 * scale,
                                 {16*5, 16 * 2, 16, 16},{});
            break;
          }

          default: {
            auto tile = scene.createEntity();
            auto& tileSprite = tile.addComponent<Sprite>();
            tileSprite.construct(tilePositionX  * scale, tilePositionY  * scale, 16 * scale, 16 * scale,
                                 {16*3, 16 * 1, 16, 16},{});
            break;
          }

        }
        tilePositionX += 16;
      }
        tilePositionX = 0;
        tilePositionY += 16;
    }
  }

  #define Shape std::variant<PolygonShape, CircleShape, EdgeShape, ChainShape>
  Shape shape = PolygonShape{};

  engine.window->addObserver(&defaultCamera);

  engine.previous = (float)glfwGetTime();

  auto characters = std::make_shared<Texture>("assets/tiny-16-basic/characters.png");

  while(!engine.window->shouldWindowClose()) {
    const auto now = (float) glfwGetTime();
    auto deltaTime = now - engine.previous;
    if(deltaTime >= 1.0f/75) {
      engine.previous = now;

      if(keys[GLFW_KEY_EQUAL]) cameraZoomIn(defaultCameraID);
      if(keys[GLFW_KEY_MINUS]) cameraZoomOut(defaultCameraID);

      if(keys[GLFW_KEY_W]) cameraMoveUp(defaultCameraID);
      if(keys[GLFW_KEY_A]) cameraMoveLeft(defaultCameraID);
      if(keys[GLFW_KEY_S]) cameraMoveDown(defaultCameraID);
      if(keys[GLFW_KEY_D]) cameraMoveRight(defaultCameraID);

    }

    auto& camera = engine.currentScene->currentCamera->getComponent<Camera>();
    engine.window->clear(255.0f, 255.0f, 255.0f, 1.0f);
    //engine.updatePhysics(engine.delta);

    engine.renderer->beginDynamicBatch(camera.mvp, *engine.shaderProgram, *texture);
    {
      auto view = engine.currentScene->registry.view<Sprite>();
      for(auto entityID : view) {
        //if(scene->registry.any_of<Player>(entityID);)
        auto &sprite = engine.currentScene->registry.get<Sprite>(entityID);
        engine.renderer->draw(sprite);
      }
    }
    engine.renderer->endDynamicBatch();

    /*engine.renderer->beginDynamicBatch(camera.mvp, *engine.shaderProgram, *characters);
    {
      engine.renderer->draw(playerSprite);
    }
    engine.renderer->endDynamicBatch();*/

    engine.window->swapBuffers();
    engine.window->pollEvents();
  }

}

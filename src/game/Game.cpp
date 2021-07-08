#include "../Engine.h"
#include "../ECS/Camera.h"

#include "../Input/Keyboard.h"
#include "Player.h"
#include <sstream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <algorithm>

// TODO:
//  Move game assets from engine into game.


struct DebugDraw : public b2Draw {

  glm::mat4 projectionMatrix;
  float pixelsPerMeter = 16;

  virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {}
  virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {

    ShaderProgram shaderProgram("shaders/defaultColorVertex.vert", "shaders/defaultColorFragment.frag");
    shaderProgram.bind();

    shaderProgram.setUniformMatrix4fv("uMVP", 1, false, glm::value_ptr(projectionMatrix));

    std::vector<float> tmpVertices;
    tmpVertices.reserve(vertexCount * 2);

    for(int i = 0; i < vertexCount; ++i) {
      tmpVertices.push_back(vertices[i].x * pixelsPerMeter);
      tmpVertices.push_back(vertices[i].y * pixelsPerMeter);
    }

    VertexArray vao;
    vao.bind();

    VertexBuffer vbo;
    ElementBuffer ebo;

    std::vector<unsigned int> indices = {
        0, 1, 2,
        2, 0, 3
    };

    vbo.bind();
    ebo.bind();

    vbo.fillBuffer(tmpVertices);
    ebo.fillBuffer(indices);

    vao.enableAttribute(0);
    vao.describeAttributeLayout(0, 2, GL_FLOAT);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

  }
  virtual void DrawCircle(const b2Vec2& center, float radius, const b2Color& color) {}
  virtual void DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color) {}
  virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {}
  virtual void DrawTransform(const b2Transform& xf) {}
  virtual void DrawPoint(const b2Vec2& p, float size, const b2Color& color) {}
};

int main() {
  #define Shape std::variant<PolygonShape, CircleShape, EdgeShape, ChainShape>

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

  auto player = engine.currentScene->createEntitySubClass<Player>();
  auto& playerSprite = player.getComponent<Sprite>();
  playerSprite.construct(450, 400,
                         16*7, 16*7, 0.0f,
                         {16*7, 48, 16, 16}, {});

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
    int scale = 4;
    int tileSize = 16 * scale;

    playerSprite.width = 16 * scale;
    playerSprite.height = 16 * scale;

    auto createTile = [&scale, &tileSize](Scene& scene, int tilePositionX, int tilePositionY, const TextureRectangle& texturePosition) {
      auto tile = scene.createEntity();
      auto& tileSprite = tile.addComponent<Sprite>();
      tileSprite.construct(tilePositionX * scale, tilePositionY * scale, tileSize, tileSize, 0.0f,
                           texturePosition,{});
    };

    auto createTileWithCollision = [&scale, &tileSize](Scene& scene, int tilePositionX, int tilePositionY, const TextureRectangle& texturePosition) {
      auto tile = scene.createEntity();
      auto& tileSprite = tile.addComponent<Sprite>();
      tileSprite.construct(tilePositionX * scale, tilePositionY * scale, tileSize, tileSize, 0.0f,
                           texturePosition,{});
      auto& body = tile.addBody();
      body.setPosition({
                           tilePositionX * scale ,
                           tilePositionY * scale
                       });
      Shape shape = PolygonShape();
      std::get<PolygonShape>(shape).setAsBox(scene.world, {tileSize, tileSize});

      body.addCollisionShape(shape);
      body.setType(Body::BodyType::STATIC_BODY);
      body.setSize({tileSize, tileSize});
    };

    while(std::getline(tmpMap, line)) {

      for(const char& i : line) {
        switch(i) {
          case 'G': {
            createTile(scene, tilePositionX, tilePositionY, {16*3, 16 * 1, 16, 16});
            break;
          }

          case 'T': {
            createTileWithCollision(scene, tilePositionX, tilePositionY, {16*4, 16 * 9, 16, 16}); // tree
            createTile(scene, tilePositionX, tilePositionY, {16*3, 16 * 1, 16, 16}); // grass
            break;
          }

          case 'W': {
            createTile(scene, tilePositionX, tilePositionY, {16*5, 16 * 2, 16, 16});
            break;
          }

          default: {
            createTile(scene, tilePositionX, tilePositionY, {16*3, 16 * 1, 16, 16});
            break;
          }

        }
        tilePositionX += 16;
      }
        tilePositionX = 0;
        tilePositionY += 16;
    }
  }

  auto characters = std::make_shared<Texture>("assets/tiny-16-basic/characters.png");

  auto& playerCamera = player.getComponent<Camera>();
  playerCamera.construct(engine.window->getViewportWidth(), engine.window->getViewportHeight());
  engine.currentScene->currentCamera = &player;

  engine.window->addObserver(&defaultCamera);
  engine.window->addObserver(&playerCamera);

  playerSprite.x = (engine.currentScene->currentCamera->getComponent<Camera>().width / 2) - playerSprite.width/2;
  playerSprite.y = (engine.currentScene->currentCamera->getComponent<Camera>().height / 2) - playerSprite.height;

  auto& body = player.getComponent<Body>();
  Shape shape = PolygonShape{};
  std::get<PolygonShape>(shape).setAsBox(engine.currentScene->world, {playerSprite.width, playerSprite.height});
  playerSprite.x = 100;
  body.setPosition({playerSprite.x, playerSprite.y});
  body.addCollisionShape(shape);

/*  auto enemy = engine.currentScene->createEntity();
  auto& enemySprite = enemy.addComponent<Sprite>();
  enemySprite.construct(400, 200, 16 * 4, 16 * 4, 0.0f, {16 * 1, 16 * 4, 16, 16}, {});
  auto& enemyBody = enemy.addBody();
  enemyBody.setType(Body::BodyType::DYNAMIC_BODY);
  Shape enemyShape = PolygonShape{};
  std::get<PolygonShape>(enemyShape).setAsBox(engine.currentScene->world, {enemySprite.width, enemySprite.height});
  enemyBody.setPosition({enemySprite.x, enemySprite.y});
  enemyBody.addCollisionShape(enemyShape);*/


  DebugDraw debugDraw;
  engine.currentScene->world.setDebugDraw(debugDraw);
  debugDraw.SetFlags(b2Draw::e_shapeBit);

  engine.previous = (float)glfwGetTime();
  while(!engine.window->shouldWindowClose()) {
    engine.updatePhysics(engine.delta);

    if(engine.delta >= engine.timeStep) {

      auto view = engine.currentScene->registry.view<Body, Sprite>();
      for(auto entityID : view) {
        auto &sprite = engine.currentScene->registry.get<Sprite>(entityID);
        auto &body = engine.currentScene->registry.get<Body>(entityID);
        auto physicsPos = body.getPosition();

        sprite.x = physicsPos.x;
        sprite.y = physicsPos.y;
        sprite.rotation = body.getAngle();
      }

      if (keys[ GLFW_KEY_EQUAL ]) cameraZoomIn(*engine.currentScene->currentCamera);
      if(keys[ GLFW_KEY_MINUS]) cameraZoomOut(*engine.currentScene->currentCamera);

      if (keys[ GLFW_KEY_W ]) {
        playerMoveUp(player);
        cameraMoveUp(*engine.currentScene->currentCamera);
        playerSprite.texturePosition = {16 * 7, 48, 16, 16};
      }

      if (keys[ GLFW_KEY_A ]) {
        playerMoveLeft(player);
        cameraMoveLeft(*engine.currentScene->currentCamera);
        playerSprite.texturePosition = {16 * 7, 16 * 1, 16, 16};
      }

      if (keys[ GLFW_KEY_S ]) {
        playerMoveDown(player);
        cameraMoveDown(*engine.currentScene->currentCamera);
        playerSprite.texturePosition = {16 * 7, 16 * 0, 16, 16};
      }

      if (keys[ GLFW_KEY_D ]) {
        playerMoveRight(player);
        cameraMoveRight(*engine.currentScene->currentCamera);
        playerSprite.texturePosition = {16 * 7, 16 * 2, 16, 16};
      }
    }

    engine.window->clear(255.0f, 255.0f, 255.0f, 1.0f);

    auto& camera = engine.currentScene->currentCamera->getComponent<Camera>();

    engine.renderer->beginDynamicBatch(camera.mvp, *engine.shaderProgram, *texture);
    {
      auto view = engine.currentScene->registry.view<Sprite>(entt::exclude<PlayerEntityID>);
      for(auto entityID : view) {
        auto &sprite = engine.currentScene->registry.get<Sprite>(entityID);
        engine.renderer->draw(sprite);
      }
    }
    engine.renderer->endDynamicBatch();


    engine.renderer->beginDynamicBatch(camera.mvp, *engine.shaderProgram, *characters);
    {
      engine.renderer->draw(playerSprite);
      //engine.renderer->draw(enemySprite);
    }
    engine.renderer->endDynamicBatch();

    debugDraw.projectionMatrix = engine.currentScene->currentCamera->getComponent<Camera>().mvp;
    engine.currentScene->world.drawDebugData();

    engine.window->swapBuffers();
    engine.window->pollEvents();
  }

}

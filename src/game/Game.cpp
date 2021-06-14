#include "../Engine.h"

#include "AL/al.h"
#include <box2d/box2d.h>

#include "../ECS/Components.h"
#include "Player.h"
#include "../Audio/AudioSource.h"
#include "../ECS/Sprite.h"
#include "../ECS/Camera.h"

#include <fstream>

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
  player.getComponent<Camera>().setWidth(engine.window->getViewportWidth());
  player.getComponent<Camera>().setHeight(engine.window->getViewportHeight());
  scene.currentCamera = &player;

  //engine.window->addObserver(&defaultCamera);
  engine.window->addObserver(&player.getComponent<Camera>());

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

  /*{
    int i = 0;
    while(1) {
      ++i;
      world.Step(timeStep, velocityIterations, positionIterations);
      std::cout << std::format("Dynamic Body Pos({}, {})", dynamicBody->GetPosition().x, dynamicBody->GetPosition().y)
                << std::endl;
      if(i >= 60 * 2000)
        return 0;
    }

    Player *player1 = static_cast<Player *>(engine.currentScene->getEntityPtr(player));
    * /
  }*/


  float scale = 4;
  for(float x = 0; x < 2; ++x) {
    for(float y = 0; y < 2; ++y) {
      auto spriteID = engine.currentScene->createEntity();
      spriteID.addComponent<Sprite>(x * 16 * scale, y * 16 * scale, 16 * scale, 16 * scale,
                                    TextureRectangle {0, 32, 16, 16}, Color {1.0f, 1.0f, 1.0f, 1.0f});
    }
  }

  auto spriteID2 = engine.currentScene->createEntity();
  spriteID2.addComponent<Sprite>(0.0f, 0.0f,
                                 engine.window->getViewportWidth(), engine.window->getViewportHeight(),
                                 TextureRectangle {0 , 0, 16, 16},
                                 Color {1.0f, 1.0f, 1.0f, 0.0f}
  );

  engine.previous = (float) glfwGetTime();

  while(!engine.window->shouldWindowClose()) {
    auto& camera = engine.currentScene->currentCamera->getComponent<Camera>();
    spriteID2.getComponent<Sprite>().width = engine.window->getViewportWidth() / (engine.window->getViewportWidth()/ 1600);
    spriteID2.getComponent<Sprite>().height = engine.window->getViewportHeight() / (engine.window->getViewportHeight()/ 900);
    engine.update(engine.delta);
    engine.render();
  }

}

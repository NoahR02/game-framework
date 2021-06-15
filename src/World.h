#ifndef RPG_WORLD_H
#define RPG_WORLD_H


#include <box2d/box2d.h>
#include <glm/vec2.hpp>
#include "ECS/Body.h"

struct World {

  World() {
    world = new b2World(b2Vec2(0.0f, 100.0f));
  }

  void createBody(Body& body) {

    body.body = world->CreateBody(&body.properties);

    b2FixtureDef dynamicFixtureDef;
    dynamicFixtureDef.shape = &body.shape;
    dynamicFixtureDef.density = 1.0f;
    auto fixture = body.body->CreateFixture(&dynamicFixtureDef);

  }

  ~World() {
    delete world;
  }

  void setScaleX(float scaleX) {
    if(scaleX != 0)
      this->scaleX = scaleX;
  }

  void setScaleY(float scaleY) {
    if(scaleY != 0)
      this->scaleY = scaleY;
  }

  float getScaleX() const {
    return scaleX;
  }
  float getScaleY() const {
    return scaleY;
  }


public:
  b2World* world;
private:
  float scaleX;
  float scaleY;

};

#endif

#include "Player.h"
#include "../ECS/Camera.h"
#include "../ECS/Components.h"
#include "../ECS/Sprite.h"
#include "../Input/Keyboard.h"

Player::Player(Scene* scene) : Entity(scene) {
  addComponent<Camera>(0, 0);
  addComponent<Sprite>(0.0f,0.0f,
                       64.0f, 64.0f,
                       TextureRectangle {16, 0, 16, 16},
                       Color {1.0f, 1.0f, 1.0f, 1.0f});
  addComponent<Components::Controller>();
  auto& playerBody = addBody(glm::vec2(0, 0));
  playerBody.setType(Body::BodyType::DYNAMIC_BODY);
}

void Player::render(float deltaTime) {
  Entity::render(deltaTime);
}

void Player::update(float deltaTime) {
  auto& playerBody = getComponent<Body>();
  auto& playerSprite = getComponent<Sprite>();

  Entity::update(deltaTime);
  auto& controller = getComponent<Components::Controller>();
  auto& sprite = getComponent<Sprite>();

  if(keys[GLFW_KEY_W]) {
    playerBody.setLinearVelocity({playerBody.getLinearVelocity().x, -speed*2});
  }
  if(keys[GLFW_KEY_A]) {
    playerBody.setLinearVelocity({-speed, playerBody.getLinearVelocity().y});
  }
  if(keys[GLFW_KEY_S]) {
    //playerBody.setLinearVelocity({playerBody.getLinearVelocity().x, speed});
  }
  if(keys[GLFW_KEY_D]) {
    playerBody.setLinearVelocity({speed, playerBody.getLinearVelocity().y});
  }

  if(keys[GLFW_KEY_EQUAL])
    cameraZoomIn(*this);
  if(keys[GLFW_KEY_MINUS])
    cameraZoomOut(*this);

  auto playerPhysicsPos = playerBody.getPosition();
  setX(playerPhysicsPos.x-playerSprite.width/2);
  setY(playerPhysicsPos.y-playerSprite.height/2);
}

void Player::setY(float y) {
  auto& sprite = getComponent<Sprite>();
  sprite.y = y;

  auto& camera = getComponent<Camera>();
  camera.view[3][1] = -y - sprite.height/2;
  cameraRecalculate(*this);
}

void Player::setX(float x) {
  auto& sprite = getComponent<Sprite>();
  sprite.x = x;

  auto& camera = getComponent<Camera>();
  camera.view[3][0] = -x - sprite.width/2;
  cameraRecalculate(*this);
}

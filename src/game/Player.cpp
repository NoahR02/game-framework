#include "Player.h"
#include "../ECS/Camera.h"
#include "../ECS/Components.h"
#include "../ECS/Sprite.h"
#include "../Input/Keyboard.h"

Player::Player(Scene* scene) : Entity(scene) {
  addComponent<Camera>(0, 0);
  addComponent<Sprite>(1200 / 2 - 32.0f,
                       1200 / 2 - 32.0f, 64.0f, 64.0f,
                       TextureRectangle {16, 16, 16, 16}, Color {1.0f, 1.0f, 1.0f, 1.0f});
  addComponent<Components::Controller>();
}

void Player::render(float deltaTime) {
  Entity::render(deltaTime);
}

void Player::update(float deltaTime) {
  Entity::update(deltaTime);
  auto& controller = getComponent<Components::Controller>();
  auto& sprite = getComponent<Sprite>();

  if(keys[GLFW_KEY_W]) {
    setY(sprite.y - speed);
  }
  if(keys[GLFW_KEY_A]) {
    setX(sprite.x - speed);
  }
  if(keys[GLFW_KEY_S]) {
    setY(sprite.y + speed);
  }
  if(keys[GLFW_KEY_D]) {
    setX(sprite.x + speed);
  }

  if(keys[GLFW_KEY_EQUAL])
    cameraZoomIn(*this);
  if(keys[GLFW_KEY_MINUS])
    cameraZoomOut(*this);
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

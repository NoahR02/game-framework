#include "Player.h"
#include "../ECS/Camera.h"
#include "../ECS/Components.h"
#include "../ECS/Sprite.h"
#include "../ECS/Systems.h"
#include "../Input/Keyboard.h"

Player::Player(Scene* scene) : Entity(scene) {
  addComponent<Camera>(0, 0);
  addComponent<Sprite>(1200 / 2 - 32.0f,
                        1200 / 2 - 32.0f, 64.0f, 64.0f,
                        TextureRectangle {16, 16, 16, 16}, Color {1.0f, 1.0f, 1.0f, 1.0f});
  addComponent<Components::Controller>();
}

void Player::render(float deltaTime) {
  //std::cout << "Rendering from player" << std::endl;
  Entity::render(deltaTime);
}

void Player::update(float deltaTime) {
  Entity::update(deltaTime);
  auto &controller = getComponent<Components::Controller>();
  auto &sprite = getComponent<Sprite>();
  auto &camera = getComponent<Camera>();

  if(keys[GLFW_KEY_W]) {
    cameraMoveUp(*this);
    sprite.y -= camera.speed;
  }
  if(keys[GLFW_KEY_A]) {
    cameraMoveLeft(*this);
    sprite.x -= camera.speed;
  }
  if(keys[GLFW_KEY_S]) {
    cameraMoveDown(*this);
    sprite.y += camera.speed;
  }
  if(keys[GLFW_KEY_D]) {
    cameraMoveRight(*this);
    sprite.x += camera.speed;
  }

  if(keys[GLFW_KEY_EQUAL])
    cameraZoomIn(*this);
  if(keys[GLFW_KEY_MINUS])
    cameraZoomOut(*this);
}

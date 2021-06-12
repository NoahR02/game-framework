#include "Player.h"
#include "ECS/Components.h"
#include "Sprite.h"

Player::Player(Scene* scene) : Entity(scene) {
  addComponent<Components::Camera>(0, 0);
  addComponent<Sprite>(1200 / 2 - 32.0f,
                        1200 / 2 - 32.0f, 64.0f, 64.0f,
                        TextureRectangle {0, 16, 16, 16}, Color {1.0f, 1.0f, 1.0f, 1.0f});
  addComponent<Components::Controller>();
}
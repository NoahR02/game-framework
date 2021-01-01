#include <glad/glad.h>
#include <iostream>
#include "Player.h"
#include "../Events/Keyboard.h"

Player::Player(Texture* texture, int x, int y, int width, int height) : GameObject(texture, x, y, width, height) {}

void Player::move() {

  if(Keyboard::keys[GLFW_KEY_W]) {
    std::cout << "W has been pressed" << std::endl;
  }

  if(Keyboard::keys[GLFW_KEY_A]) {
    std::cout << "A has been pressed" << std::endl;
  }

  if(Keyboard::keys[GLFW_KEY_S]) {
    std::cout << "S has been pressed" << std::endl;
  }

  if(Keyboard::keys[GLFW_KEY_D]) {
    std::cout << "D has been pressed" << std::endl;
  }


}

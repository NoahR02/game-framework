#include "Keyboard.h"
#include <iostream>

void Keyboard::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

  if(action == GLFW_PRESS) {
    keys[key] = true;
  } else if(action == GLFW_RELEASE) {
    keys[key] = false;
  }

}

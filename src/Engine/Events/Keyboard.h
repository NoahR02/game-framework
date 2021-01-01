
#ifndef RPG_KEYBOARD_H
#define RPG_KEYBOARD_H


#include <array>
#include <GLFW/glfw3.h>

struct Keyboard {

  inline static std::array<bool, 350> keys = {};
  static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

};


#endif //RPG_KEYBOARD_H

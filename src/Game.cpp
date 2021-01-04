#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Engine/Window.h"

int main() {

  Window window(1600, 900, "RPG");

  while(window.isOpen()) {
    window.clear();

    window.swapBuffers();
  }

  return 0;
}
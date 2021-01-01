#ifndef RPG_WINDOW_H
#define RPG_WINDOW_H

#include <GLFW/glfw3.h>
#include <string>

struct Window {
  GLFWwindow* glfwWindow;

  Window(int width, int height, const char* title);
  void enableVsync(bool enable);
  ~Window();

  void setTitle(const char* title);
  void setWidth(int width);
  void setHeight(int height);

  int getWidth();
  int getHeight();
  const char* getTitle();
private:
  std::string title = "RPG";

  void setSize(int width, int height);
};

#endif //RPG_WINDOW_H

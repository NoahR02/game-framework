#ifndef RPG_WINDOW_H
#define RPG_WINDOW_H

#include <GLFW/glfw3.h>
#include <string>

struct Window {
  GLFWwindow* glfwWindow;

  Window(int width, int height, const char* title);
  ~Window();

  bool isVisible() const;
  inline bool isOpen() const { return open; }

  void setVisible(bool visible);
  void setOpen(bool open);

  void clear() const;
  void swapBuffers() const;

  void setWidth(int width);
  void setHeight(int height);
  void setTitle(const char* title);

  int getWidth() const;
  int getHeight() const;

  std::string getTitle() const;

private:
  std::string title = "RPG";
  int width;
  int height;

  bool visible = true;
  bool open = true;
};

#endif //RPG_WINDOW_H

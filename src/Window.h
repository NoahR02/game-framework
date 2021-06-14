#ifndef RPG_WINDOW_H
#define RPG_WINDOW_H

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "events/Subject.h"

class Window : public Subject<Window> {

public:
  GLFWwindow* window{};

  Window();
  Window(float width, float height, const char* title);

  void swapBuffers();
  void pollEvents();
  bool shouldWindowClose();


  static void windowResizeCB(GLFWwindow* window, int width, int height);
  static void keyCB(GLFWwindow* window, int key, int scancode, int action, int mods);
  static void scrollCB(GLFWwindow* window, double xoffset, double yoffset);


  void setTitle(const char* title);

  void setWidth(int width);
  void setHeight(int height);
  void calculateViewport();
  float getViewportWidth();
  float getViewportHeight();
  void setSize(int width, int height);

  void setWindowPosition(int x, int y);
  void setWindowSizeLimits(int minWidth, int minHeight, int maxWidth, int maxHeight);
  void setForcedAspectRatioScaling(int aspectWidth, int aspectHeight);

  void setResizable(bool resizeable);
  void setVisible(bool visible);
  void setFullscreen(bool fullscreen);

  void setBackgroundColor(float r, float g, float b, float a);
  void setWindowIcon(const char* pathToImage);


  const std::string& getTitle() const;

  const float getWidth() const;
  const float getHeight() const;

  int getAspectRatioWidth() const;
  int getAspectRatioHeight() const;

  bool isResizable() const;
  bool isVisible() const;
  bool isFullscreen() const;

  struct RGBA getBackgroundColor() const;


  ~Window();

private:

  float width = 1280;
  float height = 720;
  float viewportWidth;
  float viewportHeight;
  std::string title = "Game";

  int aspectRatioWidth = 16;
  int aspectRatioHeight = 9;

  bool visible = true;
  bool resizable = true;
  bool fullscreen = false;

  struct RGBA {
    float r = 0.0;
    float g = 0.0;
    float b = 0.0;
    float a = 1.0;
  };

  int loadGLFW(float& width, float& height, const char* title);
  int loadGLAD();
};

#endif

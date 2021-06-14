#include <iostream>
#include "Window.h"
#include "Input/Keyboard.h"

Window::Window() {

  /// Loads GLFW AND Glad
  if (loadGLFW(width, height, title.c_str()) == -1) {
    std::cout << "GLFW has failed to load." << std::endl;
    exit(EXIT_FAILURE);
  }

}

Window::Window(float width, float height, const char *title) : width(width), height(height), title(title) {

  /// Loads GLFW AND Glad
  if (loadGLFW(this->width, this->height, this->title.c_str()) == -1) {
    std::cout << "GLFW has failed to load." << std::endl;
    exit(EXIT_FAILURE);
  }

}

void GLAPIENTRY messageCallback( GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam ) {
  if(severity != GL_DEBUG_SEVERITY_NOTIFICATION) {
    std::cerr
      << "GL CALLBACK: "
      << (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "")
      << "type = 0x" << type
      << ", severity = 0x" << severity
      << ", message = " << message
      << std::endl;
  }
}

int Window::loadGLFW(float &width, float &height, const char *title) {
  if (!glfwInit()) return -1;
  
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

  window = glfwCreateWindow((int)width, (int)height, title, nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  if (loadGLAD() == -1) {
    std::cout << "GLAD has failed to load." << std::endl;
    exit(EXIT_FAILURE);
  }
  glfwSwapInterval(0);

  calculateViewport();

  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(messageCallback, nullptr);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glfwSetWindowUserPointer(window, this);
  glfwSetWindowSizeCallback(window, windowResizeCB);
  glfwSetKeyCallback(window, keyCB);
  glfwSetScrollCallback(window, scrollCB);
  return 0;
}

int Window::loadGLAD() {
  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) return -1;
  return 0;
}

void Window::swapBuffers() {
  glfwSwapBuffers(window);
}

void Window::pollEvents() {
  glfwPollEvents();
}

bool Window::shouldWindowClose() {
  if (glfwWindowShouldClose(window)) return true;
  return false;
}


void Window::windowResizeCB(GLFWwindow *window, int width, int height) {
  Window *windowPtr = (Window *) glfwGetWindowUserPointer(window);
  windowPtr->width = width;
  windowPtr->height = height;

  windowPtr->calculateViewport();

  windowPtr->notify(*windowPtr, Event());
}

void Window::keyCB(GLFWwindow *window, int key, int scancode, int action, int mods) {
  if(action == GLFW_PRESS) keys[key] = true;
  if(action == GLFW_RELEASE) keys[key] = false;
}

void Window::scrollCB(GLFWwindow *window, double xoffset, double yoffset) {
}

float Window::getViewportWidth() {
  return viewportWidth;
}

float Window::getViewportHeight() {
  return viewportHeight;
}


const float Window::getWidth() const {
  return width;
}

const float Window::getHeight() const {
  return height;
}

const std::string &Window::getTitle() const {
  return title;
}

int Window::getAspectRatioWidth() const {
  return aspectRatioWidth;
}

int Window::getAspectRatioHeight() const {
  return aspectRatioHeight;
}

bool Window::isVisible() const {
  return visible;
}

bool Window::isResizable() const {
  return resizable;
}

bool Window::isFullscreen() const {
  return fullscreen;
}

void Window::setTitle(const char *title) { glfwSetWindowTitle(window, title); }

void Window::setWidth(int width) {
  glfwSetWindowSize(window, width, this->height);
  calculateViewport();
}

void Window::setHeight(int height) {
  glfwSetWindowSize(window, this->width, height);
  calculateViewport();
}

void Window::setSize(int width, int height) {
  glfwSetWindowSize(window, width, height);
  calculateViewport();
}

void Window::setWindowPosition(int x, int y) {
  glfwSetWindowPos(window, x, y);
}

void Window::setWindowSizeLimits(int minWidth, int minHeight, int maxWidth, int maxHeight) {
  glfwSetWindowSizeLimits(window, minWidth, minHeight, maxWidth, maxHeight);
}

void Window::setForcedAspectRatioScaling(int aspectWidth, int aspectHeight) {
  glfwSetWindowAspectRatio(window, aspectWidth, aspectHeight);
}

void Window::setResizable(bool resizeable) {
  this->resizable = resizeable;

  if (this->resizable) {
    glfwSetWindowAttrib(window, GLFW_RESIZABLE, GLFW_TRUE);
  } else {
    glfwSetWindowAttrib(window, GLFW_RESIZABLE, GLFW_FALSE);
  }

}

void Window::setVisible(bool visible) {

  this->visible = visible;

  if (visible) {
    glfwShowWindow(window);
  } else {
    glfwHideWindow(window);
  }

}

void Window::setFullscreen(bool fullscreen) {
  this->fullscreen = fullscreen;

  if (fullscreen) {
    glfwMaximizeWindow(window);
  }

}

void Window::setBackgroundColor(float r, float g, float b, float a) {
  glClearColor(r / 255, g / 255, b / 255, a);
  glClear(GL_COLOR_BUFFER_BIT);
}

void Window::setWindowIcon(const char *pathToImage) {}

Window::~Window() {
  glfwDestroyWindow(window);
  glfwTerminate();
}

void Window::calculateViewport() {
  int targetWidth = 1600;
  int targetHeight = 900;

  float targetAspectRatio = static_cast<float>(targetWidth) / static_cast<float>(targetHeight);

  // Letter box
  int transformedWidth = width;
  int transformedHeight = transformedWidth / targetAspectRatio;

  if(transformedHeight > height) {
    // Pillar box
    transformedHeight = height;
    transformedWidth = transformedHeight * targetAspectRatio;
  }

  int vpX = (width / 2) - (transformedWidth / 2);
  int vpY = (height / 2) - (transformedHeight / 2);

  viewportWidth = transformedWidth;
  viewportHeight = transformedHeight;

  glViewport(vpX, vpY, transformedWidth, transformedHeight);
}

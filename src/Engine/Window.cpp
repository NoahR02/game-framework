#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "Window.h"
#include "Events/Keyboard.h"
#include "ApplicationState.h"

void window_close_callback(GLFWwindow* window);
void window_size_callback(GLFWwindow *window, int width, int height);

Window::Window(int width, int height, const char* title) : title(title) {

  if(!glfwInit()) throw std::runtime_error("Glfw failed to load.");

  // Require core profile and set gl version to 3.3 core.
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  glfwWindowHint(GLFW_VISIBLE, false);

  // Create window and set window/opengl context.
  glfwWindow = glfwCreateWindow(width, height, this->title.c_str(), nullptr, nullptr);
  ApplicationState.windowHeight = height;
  ApplicationState.windowWidth = width;
  glfwMakeContextCurrent(glfwWindow);

  const GLFWvidmode *vm = glfwGetVideoMode(glfwGetPrimaryMonitor());
  glfwSetWindowPos(glfwWindow, (vm->width - width) / 2, (vm->height - height) / 2);

  if(glfwWindow == nullptr) {
    glfwTerminate();
    throw std::runtime_error("Glfw failed to create a window." );
  }

  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) throw std::runtime_error("Glad failed to load.");

  glfwShowWindow(glfwWindow);
  glfwSetKeyCallback(glfwWindow, Keyboard::key_callback);
  glfwSetWindowCloseCallback(glfwWindow, window_close_callback);
}

void window_close_callback(GLFWwindow* window) {
  glfwSetWindowShouldClose(window, GLFW_TRUE);
}


Window::~Window() {
  glfwDestroyWindow(glfwWindow);
  glfwTerminate();
}

void Window::enableVsync(bool enable) {
  enable ? glfwSwapInterval(1) : glfwSwapInterval(0);
}

void Window::setTitle(const char* title) { glfwSetWindowTitle(glfwWindow, title); this->title = title;  }
void Window::setWidth(int width) { setSize(width, getHeight());}
void Window::setHeight(int height) { setSize(getWidth(), height);}
void Window::setSize(int width, int height) {
  glfwSetWindowSize(glfwWindow, width, height);
  ApplicationState.windowWidth = width;
  ApplicationState.windowHeight = height;
}

int Window::getWidth() {
  int width;
  int height;
  glfwGetWindowSize(glfwWindow, &width, &height);
  return width;
}

int Window::getHeight() {
  int width;
  int height;
  glfwGetWindowSize(glfwWindow, &width, &height);
  return height;
}

const char *Window::getTitle() { return title.c_str(); }
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "Window.h"
#include "Events/Keyboard.h"

Window::Window(int width, int height, const char* title) : title(title) {

  if(!glfwInit()) throw std::runtime_error("Glfw failed to load.");

  // Require core profile and set gl version to 3.3 core.
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  glfwWindowHint(GLFW_VISIBLE, false);

  this->width = width;
  this->height = height;
  this->title = title;

  // Create window and set window/opengl context.
  glfwWindow = glfwCreateWindow(width, height, this->title.c_str(), nullptr, nullptr);
  glfwMakeContextCurrent(glfwWindow);

  if(glfwWindow == nullptr) {
    glfwTerminate();
    throw std::runtime_error("Glfw failed to create a window." );
  }

  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) throw std::runtime_error("Glad failed to load.");

  glfwShowWindow(glfwWindow);
}

Window::~Window() {
  glfwDestroyWindow(glfwWindow);
  glfwTerminate();
}

void Window::clear() const {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void Window::swapBuffers() const {
  glfwSwapBuffers(glfwWindow);
  glfwPollEvents();
}

void Window::setTitle(const char* title) { glfwSetWindowTitle(glfwWindow, title); this->title = title;  }
void Window::setWidth(int width) { this->width = width;  glfwSetWindowSize(glfwWindow, this->width, height); }
void Window::setHeight(int height) { this->height = height;  glfwSetWindowSize(glfwWindow, width, this->height);}

int Window::getWidth() const { return width; }
int Window::getHeight() const { return height; }
std::string Window::getTitle() const { return title; }

bool Window::isVisible() const { return visible; }

void Window::setVisible(bool visible) {
  this->visible = visible;
  if(this->visible) glfwShowWindow(glfwWindow);
  if(!this->visible) glfwHideWindow(glfwWindow);
}

void Window::setOpen(bool open) { this->open = open; }

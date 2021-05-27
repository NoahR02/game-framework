#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(int width, int height) {
  projection = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height),0.0f);
  view = glm::translate(glm::mat4(1.0f),glm::vec3(0.0f, 0.0f, 0.0f));
  mvp = projection * view;
}

void Camera::moveLeft() {
  view = glm::translate(view, glm::vec3(speed, 0.0f, 0.0f));
  mvp = projection * view;
}

void Camera::moveRight() {
  view = glm::translate(view, glm::vec3(-speed, 0.0f, 0.0f));
  mvp = projection * view;
}

void Camera::moveUp() {
  view = glm::translate(view, glm::vec3(0.0f, speed, 0.0f));
  mvp = projection * view;
}

void Camera::moveDown() {
  view = glm::translate(view, glm::vec3(0.0f, -speed, 0.0f));
  mvp = projection * view;
}

void Camera::zoomIn() {
  zoomLevel += 0.001f;
  mvp = projection * view;
  mvp = glm::scale(mvp, glm::vec3(zoomLevel));
}

void Camera::zoomOut() {
  zoomLevel -= 0.001f;
  mvp = projection * view;
  mvp = glm::scale(mvp, glm::vec3(zoomLevel));
}

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "Camera.h"

Camera::Camera(float left, float right, float bottom, float top) : p(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)),
v(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f))) {}

void Camera::moveLeft() {
  v = glm::translate(v, glm::vec3(-0.003f, 0.0f, 0.0f));
}

void Camera::moveRight() {
  v = glm::translate(v, glm::vec3(0.003f, 0.0f, 0.0f));
}

void Camera::moveUp() {
  v = glm::translate(v, glm::vec3(0.0f, 0.003f, 0.0f));
}

void Camera::moveDown() {
  v = glm::translate(v, glm::vec3(0.0f, -0.003f, 0.0f));
}

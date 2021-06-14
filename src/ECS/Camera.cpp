#include "Camera.h"

Camera::Camera(float width, float height) : width(width), height(height) {
  projection = glm::ortho(0.0f, width, height, 0.0f);
  view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
  mvp = projection * view;
}


void Camera::onNotify(Window &window, Event event) {
  setWidth(window.getViewportWidth());
  setHeight(window.getViewportHeight());
}

void cameraMoveLeft(Entity& entity) {

  auto& camera = entity.getComponent<Camera>();

  camera.view = glm::translate(camera.view, glm::vec3(camera.speed, 0.0f, 0.0f));
  camera.mvp = camera.projection * camera.view;
}

void cameraMoveRight(Entity& entity) {

  auto& camera = entity.getComponent<Camera>();

  camera.view = glm::translate(camera.view, glm::vec3(-camera.speed, 0.0f, 0.0f));
  camera.mvp = camera.projection * camera.view;
}

void cameraMoveUp(Entity& entity) {

  auto& camera = entity.getComponent<Camera>();

  camera.view = glm::translate(camera.view, glm::vec3(0.0f, camera.speed, 0.0f));
  camera.mvp = camera.projection * camera.view;
}

void cameraMoveDown(Entity& entity) {

  auto& camera = entity.getComponent<Camera>();

  camera.view = glm::translate(camera.view, glm::vec3(0.0f, -camera.speed, 0.0f));
  camera.mvp = camera.projection * camera.view;
}


void cameraZoomIn(Entity& entity) {
  auto& camera = entity.getComponent<Camera>();

  camera.zoomLevel += 0.01f;
  camera.projection = glm::ortho(0.0f, camera.width/camera.zoomLevel, camera.height/camera.zoomLevel, 0.0f)
                      * glm::scale(glm::mat4(1.0f), glm::vec3(camera.width / 1600, camera.height / 900, 1.0f));
  camera.mvp = camera.projection * camera.view;
}

void cameraZoomOut(Entity& entity) {
  auto& camera = entity.getComponent<Camera>();

  camera.zoomLevel -= 0.01f;
  camera.projection = glm::ortho(0.0f, camera.width/camera.zoomLevel, camera.height/camera.zoomLevel, 0.0f)
               * glm::scale(glm::mat4(1.0f), glm::vec3(camera.width / 1600, camera.height / 900, 1.0f));

  camera.mvp = camera.projection * camera.view;
}



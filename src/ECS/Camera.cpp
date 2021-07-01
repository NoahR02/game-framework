#include "Camera.h"

Camera::Camera(float width, float height) : width(width), height(height) {

  int viewportXAndY[2];
  glGetIntegerv(GL_VIEWPORT, viewportXAndY);

  zoomLevel = 1;
  projection =
      glm::ortho((float)viewportXAndY[0], width / 2 / zoomLevel, height / 2 / zoomLevel, (float)viewportXAndY[1])
      * glm::scale(glm::mat4(1.0f), glm::vec3(width / 1600, height / 900, 1.0f));
  view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
  mvp = projection * view;
}


void Camera::onNotify(Window& window, Event event) {
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

  camera.projection = glm::ortho(-camera.width / 2 / camera.zoomLevel, camera.width / 2 / camera.zoomLevel,
                                 camera.height / 2 / camera.zoomLevel, -camera.height / 2 / camera.zoomLevel)
                      * glm::scale(glm::mat4(1.0f), glm::vec3(camera.width / 1600, camera.height / 900, 1.0f));
  camera.mvp = camera.projection * camera.view;

}

void cameraZoomOut(Entity& entity) {

  auto& camera = entity.getComponent<Camera>();

  camera.zoomLevel -= 0.01f;
  camera.projection = glm::ortho(-camera.width / 2 / camera.zoomLevel, camera.width / 2 / camera.zoomLevel,
                                 camera.height / 2 / camera.zoomLevel, -camera.height / 2 / camera.zoomLevel)
                      * glm::scale(glm::mat4(1.0f), glm::vec3(camera.width / 1600, camera.height / 900, 1.0f));

  camera.mvp = camera.projection * camera.view;

}

void cameraRecalculate(Entity& entity) {
  auto& camera = entity.getComponent<Camera>();

  camera.projection = glm::ortho(-camera.width / 2 / camera.zoomLevel, camera.width / 2 / camera.zoomLevel,
                                 camera.height / 2 / camera.zoomLevel, -camera.height / 2 / camera.zoomLevel)
                      * glm::scale(glm::mat4(1.0f), glm::vec3(camera.width / 1600, camera.height / 900, 1.0f));

  camera.mvp = camera.projection * camera.view;
}



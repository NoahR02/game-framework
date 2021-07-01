#ifndef RPG_CAMERA_H
#define RPG_CAMERA_H

#include "Entity.h"
#include "../Window.h"

#include <GLFW/glfw3native.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Camera : Observer<Window> {
  float zoomLevel = 1.0f;
  float speed = 4.0f;

  float width;
  float height;

  glm::mat4 projection;
  glm::mat4 view;
  glm::mat4 mvp;


  Camera(float width, float height);
  void onNotify(Window& window, Event event) override;

  void setWidth(const float width) {
    int viewportXAndY[2];
    glGetIntegerv(GL_VIEWPORT, viewportXAndY);
    this->width = width;
    projection = glm::ortho((float)viewportXAndY[0], width / 2 / zoomLevel,
                                   height / 2 / zoomLevel, (float)viewportXAndY[1])
                        * glm::scale(glm::mat4(1.0f), glm::vec3(width / 1600, height / 900, 1.0f));
    mvp = projection * view;
  }

  void setHeight(const float height) {
    int viewportXAndY[2];
    glGetIntegerv(GL_VIEWPORT, viewportXAndY);
    this->height = height;
    projection = glm::ortho((float)viewportXAndY[0], width / 2 / zoomLevel,
                            height / 2 / zoomLevel, (float)viewportXAndY[1])
                 * glm::scale(glm::mat4(1.0f), glm::vec3(width / 1600, height / 900, 1.0f));
    mvp = projection * view;
  }

};

void cameraMoveLeft(Entity& entity);
void cameraMoveRight(Entity& entity);
void cameraMoveUp(Entity& entity);
void cameraMoveDown(Entity& entity);
void cameraZoomIn(Entity& entity);
void cameraZoomOut(Entity& entity);
void cameraRecalculate(Entity& entity);

#endif //RPG_CAMERA_H

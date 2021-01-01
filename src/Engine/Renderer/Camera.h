#ifndef RPG_CAMERA_H
#define RPG_CAMERA_H


#include <glm/glm.hpp>

struct Camera {
  Camera(float left, float right, float bottom, float top);

  void moveLeft();
  void moveRight();
  void moveUp();
  void moveDown();

  glm::mat4 p;
  glm::mat4 v;
  glm::mat4 m;

  glm::vec3 up = {0.0f, 1.0f, 0.0f};
  glm::vec3 left = {-1.0f, 0.0f, 0.0f};
  glm::vec3 down = {0.0f, -1.0f, 0.0f};
  glm::vec3 right = {1.0f, 0.0f, 0.0f};


  glm::vec3 position = {0.0f, 0.0f, 0.0f};
};


#endif //RPG_CAMERA_H

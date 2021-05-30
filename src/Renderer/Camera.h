#ifndef RPG_CAMERA_H
#define RPG_CAMERA_H

#include <glm/glm.hpp>

class Camera {

private:
  const float speed = 4.0f;

public:
  glm::mat4 projection;
  glm::mat4 view;
  glm::mat4 mvp;

  float zoomLevel = 1.0f;

  Camera(int width, int height);

  void moveLeft();
  void moveRight();

  void moveUp();
  void moveDown();

  void zoomIn(const int& windowWidth, const int& windowHeight);
  void zoomOut(const int& windowWidth, const int& windowHeight);

  ~Camera() = default;
};


#endif //RPG_CAMERA_H

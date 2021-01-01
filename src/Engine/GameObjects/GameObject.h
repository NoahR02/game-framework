#ifndef RPG_GAMEOBJECT_H
#define RPG_GAMEOBJECT_H

#include <memory>
#include <vector>
#include "../Renderer/VertexBuffer.h"
#include "../Renderer/ElementBuffer.h"
#include "../Renderer/Texture.h"
#include "../Renderer/Program.h"
#include "../Renderer/FrameBuffer.h"

struct GameObject {

  int x = 0;
  int y = 0;
  int width = 0;
  int height = 0;

  GameObject(Texture* texture, int x, int y, int width, int height);
  void move();
  ~GameObject();

  void setProgram(const char* vertexShaderSource, const char* fragmentShaderSource);

  VertexBuffer* vbo;
  ElementBuffer* ebo;
  Texture* texture;

  Program* program = nullptr;

  std::vector<float> vertices = {
    // pos                                                   // tex pos
    (float)x + width, (float)y, 0.0f,                        1.0f, 1.0f,              // top right
    (float)x, (float)y, 0.0f,                                0.0f, 1.0f,              // top left
    (float)x, (float)y - height, 0.0f,                       0.0f, 0.0f,              // bottom left
    (float)x + width, (float)y - height, 0.0f,               1.0f, 0.0f,              // bottom right
  };

  std::vector<unsigned int> indices = {
    0, 1, 2,
    0, 2, 3
  };


};


#endif //RPG_GAMEOBJECT_H

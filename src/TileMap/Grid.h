#ifndef RPG_GRID_H
#define RPG_GRID_H


#include "../Renderer/ShaderProgram.h"
#include "../Renderer/VertexArray.h"
#include "../Renderer/VertexBuffer.h"
#include "../Renderer/Camera.h"

#include <memory>

struct Grid {

private:
  std::unique_ptr<ShaderProgram> shaderProgram;
  std::unique_ptr<VertexArray> vao;
  std::vector<float> points;
  std::unique_ptr<VertexBuffer> pointsVBO;

public:
  Grid(const int& width, const int& height, int tileWidth, int tileHeight);

  void calculateGridSize(const int& width, const int height, int tileWidth, int tileHeight);
  void draw(const Camera& camera);

};



#endif //RPG_GRID_H

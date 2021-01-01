#ifndef RPG_PLAYER_H
#define RPG_PLAYER_H


#include "GameObject.h"

struct Player : public GameObject {

  Player(Texture* texture, int x, int y, int width, int height);

  void move();


  const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 pos;
    layout (location = 1) in vec2 tex;
    out vec2 texCoords;
    uniform mat4 proj;

    void main() {
      gl_Position = proj * vec4(pos, 1.0f);
      texCoords = tex;
    }
  )";

  const char* fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;
    in vec2 texCoords;
    uniform sampler2D theTexture;

    void main() {
      FragColor = vec4(1,0,1, 1);
    }
  )";



};


#endif //RPG_PLAYER_H

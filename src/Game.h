
#ifndef RPG_GAME_H
#define RPG_GAME_H

#include <filesystem>
#include "Engine/Renderer/Renderer.h"
#include "Engine/LevelEditor/LevelEditor.h"

struct Game {
  Window* window;
  Renderer* renderer;

  std::filesystem::path assetsPath = std::filesystem::current_path().append("assets");

  Game();
  void start();
  void update();
  void render();
  ~Game();

  SpriteSheet* basicTiles;
  SpriteSheet*  characters;

  Texture* grassTexture;
  GameObject* grass;

  Texture* princessTexture;
  Player* princess;

  Texture* ghostTexture;
  GameObject* ghost;

  LevelEditor* levelEditor;

  FrameBuffer* frameBuffer;

  const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 pos;
    layout (location = 1) in vec2 tex;
    out vec2 texCoords;
    uniform mat4 mvp;

    void main() {
      gl_Position = mvp * vec4(pos, 1.0f);
      texCoords = tex;
    }
  )";

  const char* fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;
    in vec2 texCoords;
    uniform sampler2D theTexture;

    void main() {
      FragColor = vec4(1.0f, 0.0f, 1.0f, 1.0f) * texture(theTexture, texCoords);
    }
  )";
};

#endif //RPG_GAME_H

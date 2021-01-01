#ifndef RPG_RENDERER_H
#define RPG_RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../GameObjects/GameObject.h"
#include "VertexArray.h"
#include "Camera.h"
#include "../Window.h"

struct Renderer {

  Renderer();
  ~Renderer();
  VertexArray* vao;
  Camera* camera;
  void draw(GameObject& gameObject) const;
  void clear();
  void swapBuffersAndPollEvents(GLFWwindow* glfwWindow);

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
      FragColor = texture(theTexture, texCoords);
    }
  )";

  Shader* vertexShader = new Shader(GL_VERTEX_SHADER, vertexShaderSource);
  Shader* fragmentShader = new Shader(GL_FRAGMENT_SHADER, fragmentShaderSource);
  Program* defaultProgram = new Program({*vertexShader, *fragmentShader});
};




#endif //RPG_RENDERER_H

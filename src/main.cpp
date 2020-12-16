#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Renderer/VertexArray.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/ElementBuffer.h"
#include "Renderer/Shader.h"
#include "Renderer/Program.h"
#include "Renderer/Texture.h"

int main() {

  if(!glfwInit()) {
    std::cout << "Glfw failed to load." << std::endl;
    return -1;
  }

  // Require core profile and set gl version to 3.3 core.
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create window and set window/opengl context.
  GLFWwindow* glfwWindow = glfwCreateWindow(1280, 720, "RPG", nullptr, nullptr);
  glfwMakeContextCurrent(glfwWindow);

  // Turn Vsync on.
  glfwSwapInterval(1);

  if(glfwWindow == nullptr) {
    glfwTerminate();
    std::cout << "Glfw failed to create a window." << std::endl;
    return -1;
  }

  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Glad failed to load." << std::endl;
    return -1;
  }

  float size = 64.0f;

  std::vector<float> vertices = {
    // pos                                              //tex
    500.0f + size, 500.0f, 0.0f,                        1.0f, 1.0f,              // top right
    500.0f, 500.0f, 0.0f,                               0.0f, 1.0f,              // top left
    500.0f, 500.0f - size, 0.0f,                        0.0f, 0.0f,              // bottom left
    500.0f + size, 500.0f - size, 0.0f,                 1.0f, 0.0f,              // bottom right
  };

  std::vector<unsigned int> indices = {
    0, 1, 2,
    0, 2, 3
  };

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
      FragColor = texture(theTexture, texCoords);
    }
  )";

  Shader vertex(GL_VERTEX_SHADER, vertexShaderSource);
  Shader fragment(GL_FRAGMENT_SHADER, fragmentShaderSource);

  Program program({vertex, fragment});
  program.bind();


  VertexArray vao;
  vao.bind();

  VertexBuffer vbo;
  vbo.bind();

  ElementBuffer ebo;
  ebo.bind();

  vbo.buffer(sizeof(float) * vertices.size(), &vertices.front(), GL_STATIC_DRAW);
  ebo.buffer(sizeof(unsigned int) * indices.size(), &indices.front(), GL_STATIC_DRAW);

  vao.vertexAttribLayout(0, 3, GL_FLOAT, false, sizeof(float) * 5, nullptr);
  vao.enableAttribute();

  vao.vertexAttribLayout(1, 2, GL_FLOAT, false, sizeof(float) * 5, (const void*)(sizeof(float) * 3));
  vao.enableAttribute(1);

  std::string path = "C:\\Users\\Lucy\\projects\\MinecraftClone\\assets\\textures\\texture.png";
  Texture texture(path);
  texture.bind();

  program.uniform1i("theTexture", 0);
  program.uniformMatrix4fv("proj");

  while(!glfwWindowShouldClose(glfwWindow)) {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

    glfwSwapBuffers(glfwWindow);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void windowCloseCallback(GLFWwindow* window) {  }

void framebufferSizeCallback(GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); }

void GLAPIENTRY messageCallback( GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam ) {
  std::cerr
  << "GL CALLBACK: "
  << (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" )
  << "type = 0x" << type
  <<  ", severity = 0x" << severity
  << ", message = " << message
  << std::endl;
}

std::string readFile(const std::string& path) {
  std::ifstream file{path};
  std::string fileString;
  std::string lineReader;

  while(std::getline(file, lineReader)) fileString += lineReader + "\n";
  file.close();

  return fileString;
}


int main() {
  GLFWwindow* window;

  if(!glfwInit()) return -1;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

  window = glfwCreateWindow(640, 480, "RPG", nullptr, nullptr);
  if(!window) { glfwTerminate(); return -1;}

  glfwMakeContextCurrent(window);
  gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

  glfwSetWindowCloseCallback(window, windowCloseCallback);
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

  glViewport(0, 0, 640, 480);

  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(messageCallback, nullptr );

  std::string vertexShaderSource = readFile("shaders/vertex.vert");
  std::string fragmentShaderSource = readFile("shaders/fragment.frag");

  unsigned int program = glCreateProgram();
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  const char* tmpVertexString = vertexShaderSource.c_str();
  const char* tmpFragmentString = fragmentShaderSource.c_str();

  glShaderSource(vertexShader, 1, &tmpVertexString, nullptr);
  glShaderSource(fragmentShader, 1, &tmpFragmentString, nullptr);

  glCompileShader(vertexShader);
  glCompileShader(fragmentShader);

  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);

  glLinkProgram(program);

  std::vector<float> vertices = {
    -0.5f, 0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f
  };

  std::vector<unsigned int> indices = {
    0, 1, 2,
    2, 1, 3
  };

  unsigned int vao;
  unsigned int vbo;
  unsigned int ebo;

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(float) * vertices.size()), &vertices.front(), GL_STATIC_DRAW);

  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(unsigned int) * indices.size()), &indices.front(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, nullptr);
  glEnableVertexAttribArray(0);

  glUseProgram(program);

  while(!glfwWindowShouldClose(window)) {
    glClearColor(0.3f, 0.5f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, nullptr);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  glDeleteProgram(program);

  glfwTerminate();
  return 0;
}
#include "ShaderProgram.h"
#include "../Utils/ReadFile.h"

ShaderProgram::ShaderProgram(const std::string &vertexShaderPath, const std::string &fragmentShaderPath) {
  rendererID = glCreateProgram();

  std::string vertexShaderSource = readFile(vertexShaderPath);
  std::string fragmentShaderSource = readFile(fragmentShaderPath);

  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  const char* tmpVertexString = vertexShaderSource.c_str();
  const char* tmpFragmentString = fragmentShaderSource.c_str();

  glShaderSource(vertexShader, 1, &tmpVertexString, nullptr);
  glShaderSource(fragmentShader, 1, &tmpFragmentString, nullptr);

  glCompileShader(vertexShader);
  glCompileShader(fragmentShader);

  glAttachShader(rendererID, vertexShader);
  glAttachShader(rendererID, fragmentShader);

  glLinkProgram(rendererID);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

void ShaderProgram::attachShader(const std::string &path, GLenum type) {
  std::string shaderSource = readFile(path);

  unsigned int shader = glCreateShader(type);

  const char* tmpShaderString = shaderSource.c_str();

  glShaderSource(shader, 1, &tmpShaderString, nullptr);

  glCompileShader(shader);

  glAttachShader(rendererID, shader);
  glLinkProgram(rendererID);

  glDeleteShader(shader);
}

void ShaderProgram::bind() {
  glUseProgram(rendererID);
}

void ShaderProgram::unBind() {
  glUseProgram(0);
}

ShaderProgram::~ShaderProgram() {
  glDeleteProgram(rendererID);
}

void ShaderProgram::setUniformMatrix4fv(const std::string &uniformName, int count, bool transpose, const float *value) {
  glUniformMatrix4fv(glGetUniformLocation(rendererID, uniformName.c_str()), count, transpose, value);
}

void ShaderProgram::setUniform1i(const std::string &uniformName, int value) {
  glUniform1i(glGetUniformLocation(rendererID, uniformName.c_str()), value);
}

void ShaderProgram::setUniform4f(const std::string &uniformName, float r, float g, float b, float a) {
  glUniform4f(glGetUniformLocation(rendererID, uniformName.c_str()), r, g, b, a);
}

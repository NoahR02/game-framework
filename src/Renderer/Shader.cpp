#include <glad/glad.h>
#include "Shader.h"

Shader::Shader(unsigned int type, const char* shaderSource) {
  rendererID = glCreateShader(type);
  glShaderSource(rendererID, 1, &shaderSource, nullptr);
  glCompileShader(rendererID);
}

Shader::Shader(unsigned int type, std::string fileName) {
  //Todo
}

unsigned int Shader::getID() {
  return rendererID;
}

Shader::~Shader() {
  glDeleteShader(rendererID);
}

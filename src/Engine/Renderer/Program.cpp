#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <iostream>
#include "Program.h"

Program::Program(std::vector<Shader> shaders) {
  rendererID = glCreateProgram();

  for(Shader shader : shaders) glAttachShader(rendererID, shader.getID());

  glLinkProgram(rendererID);
}

void Program::bind() {
  glUseProgram(rendererID);
}

void Program::unbind() {
  glUseProgram(0);
}

Program::~Program() {
  unbind();
  glDeleteProgram(rendererID);
}

void Program::uniform1i(const char *uniformName, int data) {
  glUniform1i(glGetUniformLocation(rendererID, uniformName), data);
}

void Program::uniformMatrix4fv(const char *uniformName, glm::mat4 mvp) {
  glUniformMatrix4fv(glGetUniformLocation(rendererID, uniformName), 1, GL_FALSE, &mvp[0][0]);
}
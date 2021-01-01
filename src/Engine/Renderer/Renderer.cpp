#include <iostream>
#include <memory>
#include "Renderer.h"
#include "../GameObjects/Player.h"
#include "../ApplicationState.h"

Renderer::Renderer() {
  camera = new Camera(0, 1600, 0, 900);
  vao = new VertexArray();
  vao->bind();

  glLinkProgram(defaultProgram->rendererID);
  defaultProgram->bind();
  defaultProgram->uniform1i("theTexture", 0);
  defaultProgram->uniformMatrix4fv("mvp",camera->v * camera->p);
}

void Renderer::draw(GameObject& gameObject) const {
  gameObject.vbo->bind();
  gameObject.ebo->bind();
  gameObject.texture->bind();

  if(gameObject.program == nullptr) {
    defaultProgram->bind();
    defaultProgram->uniform1i("theTexture", 0);
    defaultProgram->uniformMatrix4fv("mvp", camera->v * camera->p);
  } else {
    gameObject.program->bind();
    gameObject.program->uniform1i("theTexture", 0);
    gameObject.program->uniformMatrix4fv("mvp", camera->p);
  }

  vao->vertexAttribLayout(0, 3, GL_FLOAT, false, sizeof(float) * 5, nullptr);
  vao->enableAttribute();
  vao->vertexAttribLayout(1, 2, GL_FLOAT, false, sizeof(float) * 5, (const void*)(sizeof(float) * 3));
  vao->enableAttribute(1);

  glDrawElements(GL_TRIANGLES, gameObject.indices.size(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::clear() {
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::swapBuffersAndPollEvents(GLFWwindow* glfwWindow) {
  glfwSwapBuffers(glfwWindow);
  glfwPollEvents();
}

Renderer::~Renderer() {
  delete vertexShader;
  delete fragmentShader;

  delete defaultProgram;
  delete vao;
  delete camera;
}
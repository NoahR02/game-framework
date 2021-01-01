#include <glad/glad.h>
#include <iostream>
#include "ElementBuffer.h"

ElementBuffer::ElementBuffer() {
  glGenBuffers(1, &rendererID);
}

void ElementBuffer::bind() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
}

void ElementBuffer::unBind() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ElementBuffer::buffer(signed long int sizeOfBuffer, const void *positions, unsigned int drawCall) {
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeOfBuffer, positions, drawCall);
}

ElementBuffer::~ElementBuffer() {
  unBind();
  glDeleteBuffers(1, &rendererID);
}

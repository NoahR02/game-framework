#include <glad/glad.h>
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer() {
  glGenBuffers(1, &rendererID);
}

void VertexBuffer::bind() {
  glBindBuffer(GL_ARRAY_BUFFER, rendererID);
}

void VertexBuffer::unBind() {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::buffer(signed long int sizeOfBuffer, const void *positions, unsigned int drawCall) {
  glBufferData(GL_ARRAY_BUFFER, sizeOfBuffer, positions, drawCall);
}

VertexBuffer::~VertexBuffer() {
  unBind();
  glDeleteBuffers(1, &rendererID);
}

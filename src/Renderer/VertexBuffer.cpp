#include "VertexBuffer.h"

VertexBuffer::VertexBuffer() {
  glGenBuffers(1, &rendererID);
}

void VertexBuffer::fillBuffer(std::vector<float>& data, GLenum usage) {
  glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(float) * data.size()), &data.front(), usage);
}

void VertexBuffer::fillBuffer(long size, GLenum usage) {
  glBufferData(GL_ARRAY_BUFFER, size, nullptr, usage);
}

void VertexBuffer::fillBufferSubData(std::vector<float> &data, int offset) {
  glBufferSubData(GL_ARRAY_BUFFER, (intptr_t)offset, static_cast<GLsizeiptr>(sizeof(float) * data.size()), &data.front());
}

void VertexBuffer::bind() {
  glBindBuffer(GL_ARRAY_BUFFER, rendererID);
}

void VertexBuffer::unBind() {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::~VertexBuffer() {
  glDeleteBuffers(1, &rendererID);
}

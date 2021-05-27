#include "VertexBuffer.h"

VertexBuffer::VertexBuffer() {
  glGenBuffers(1, &rendererID);
}

void VertexBuffer::fillBuffer(std::vector<float>& data, GLenum usage) {
  glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(float) * data.size()), &data.front(), usage);
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
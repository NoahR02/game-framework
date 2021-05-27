#include "ElementBuffer.h"

ElementBuffer::ElementBuffer() {
  glGenBuffers(1, &rendererID);
}

void ElementBuffer::fillBuffer(std::vector<unsigned int>& data, GLenum usage) {
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(unsigned int) * data.size()), &data.front(), usage);
}

void ElementBuffer::bind() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
}

void ElementBuffer::unBind() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

ElementBuffer::~ElementBuffer() {
  glDeleteBuffers(1, &rendererID);
}

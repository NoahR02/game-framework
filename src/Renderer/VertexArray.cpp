#include <cstdint>
#include "VertexArray.h"

VertexArray::VertexArray() {
  glGenVertexArrays(1, &rendererID);
}

void VertexArray::describeAttributeLayout(unsigned int attribute, int size, GLenum type, bool normalized, int stride, int offset) {
  glVertexAttribPointer(attribute, size, type, normalized,  stride, (void *)(intptr_t)offset);
}

void VertexArray::enableAttribute(unsigned int attribute) {
  glEnableVertexAttribArray(attribute);
}

void VertexArray::disableAttribute(unsigned int attribute) {
  glDisableVertexAttribArray(attribute);
}

void VertexArray::bind() {
  glBindVertexArray(rendererID);
}

void VertexArray::unBind() {
  glBindVertexArray(0);
}

VertexArray::~VertexArray() {
  glDeleteVertexArrays(1, &rendererID);
}


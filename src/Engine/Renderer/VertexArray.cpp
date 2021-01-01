#include <glad/glad.h>
#include "VertexArray.h"

VertexArray::VertexArray() {
  glGenVertexArrays(1, &rendererID);
}

void VertexArray::bind() {
  glBindVertexArray(rendererID);
}

void VertexArray::unBind() {
  glBindVertexArray(0);
}

void VertexArray::enableAttribute(int attribute) {
  glEnableVertexAttribArray(attribute);
}

void VertexArray::disableAttribute(int attribute) {
  glDisableVertexAttribArray(attribute);
}

void VertexArray::vertexAttribLayout(int attribute, int attributeLength, int type, int normalized, int stride,
                                     const void *pointer) {
  glVertexAttribPointer(attribute, attributeLength, type, normalized, stride, pointer);
}

VertexArray::~VertexArray() {
  unBind();
  glDeleteVertexArrays(1, &rendererID);
}

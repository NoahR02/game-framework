#include <stb_image/stb_image.h>
#include "Renderer.h"
#include "FrameBuffer.h"


FrameBuffer::FrameBuffer(Window& window) {
  glGenFramebuffers(1, &rendererID);
  bind();
  frameBufferTexture.init(window.getWidth(), window.getHeight());
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, frameBufferTexture.rendererID, 0);
}

void FrameBuffer::FrameBufferTexture::init(int width, int height) {
  glGenTextures(1, &rendererID);
  bind();
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  unbind();
}

void FrameBuffer::FrameBufferTexture::bind() { glBindTexture(GL_TEXTURE_2D, rendererID);}
void FrameBuffer::FrameBufferTexture::unbind() { glBindTexture(GL_TEXTURE_2D, 0);}
FrameBuffer::FrameBufferTexture::~FrameBufferTexture() { glDeleteTextures(1, &rendererID);}


void FrameBuffer::bind() { glBindFramebuffer(GL_FRAMEBUFFER, rendererID);}
void FrameBuffer::unBind() { glBindFramebuffer(GL_FRAMEBUFFER, 0);}

FrameBuffer::~FrameBuffer() {
  glDeleteFramebuffers(1, &rendererID);
}

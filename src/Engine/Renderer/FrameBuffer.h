#ifndef RPG_FRAMEBUFFER_H
#define RPG_FRAMEBUFFER_H


#include "Texture.h"
#include "../Window.h"

struct FrameBuffer {

  unsigned int rendererID;

  FrameBuffer(Window& window);
  void bind();
  void unBind();
  ~FrameBuffer();

  struct FrameBufferTexture {
    unsigned int rendererID;
    FrameBufferTexture() = default;
    void init(int width, int height);
    void bind();
    void unbind();
    ~FrameBufferTexture();
  };

  FrameBufferTexture frameBufferTexture;

};


#endif //RPG_FRAMEBUFFER_H

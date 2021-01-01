#ifndef RPG_LEVELEDITOR_H
#define RPG_LEVELEDITOR_H

#include "../Window.h"
#include "../Renderer/FrameBuffer.h"

struct LevelEditor {
  Window* window;
  FrameBuffer* frameBuffer;
  LevelEditor(Window& window, FrameBuffer& frameBuffer);
  ~LevelEditor();

  void render();
};


#endif //RPG_LEVELEDITOR_H

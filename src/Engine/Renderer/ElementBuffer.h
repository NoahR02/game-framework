#ifndef MINECRAFTCLONE_ELEMENTBUFFER_H
#define MINECRAFTCLONE_ELEMENTBUFFER_H


struct ElementBuffer {
  unsigned int rendererID;

  ElementBuffer();
  void bind();
  void unBind();
  void buffer(signed long int sizeOfBuffer, const void* positions, unsigned int drawCall);
  ~ElementBuffer();
};


#endif //MINECRAFTCLONE_ELEMENTBUFFER_H

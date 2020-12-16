#ifndef MINECRAFTCLONE_ELEMENTBUFFER_H
#define MINECRAFTCLONE_ELEMENTBUFFER_H


class ElementBuffer {

private:
  unsigned int rendererID;
public:

  ElementBuffer();
  void bind();
  void unBind();
  void buffer(signed long int sizeOfBuffer, const void* positions, unsigned int drawCall);
  ~ElementBuffer();


};


#endif //MINECRAFTCLONE_ELEMENTBUFFER_H

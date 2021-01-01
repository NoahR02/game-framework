#ifndef MINECRAFTCLONE_VERTEXBUFFER_H
#define MINECRAFTCLONE_VERTEXBUFFER_H


struct VertexBuffer {
  unsigned int rendererID;

  VertexBuffer();
  void bind();
  void unBind();
  void buffer(signed long int sizeOfBuffer, const void* positions, unsigned int drawCall);
  ~VertexBuffer();
};


#endif //MINECRAFTCLONE_VERTEXBUFFER_H

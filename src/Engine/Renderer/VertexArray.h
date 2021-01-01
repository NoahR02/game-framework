#ifndef MINECRAFTCLONE_VERTEXARRAY_H
#define MINECRAFTCLONE_VERTEXARRAY_H


struct VertexArray {
  unsigned int rendererID;

  VertexArray();
  void bind();
  void unBind();
  void enableAttribute(int attribute = 0);
  void disableAttribute(int attribute = 0);
  void vertexAttribLayout(int attribute = 0, int attributeLength = 3, int type = 0x1406 /* Float */, int normalized = false,
                          int stride = 0, const void* pointer = (const void *)0);
  ~VertexArray();
};


#endif //MINECRAFTCLONE_VERTEXARRAY_H

#ifndef MINECRAFTCLONE_PROGRAM_H
#define MINECRAFTCLONE_PROGRAM_H


#include <vector>
#include "Shader.h"

class Program {

private:
  unsigned int rendererID;

public:
  Program() = default;
  Program(std::vector<Shader> shaders);
  void bind();
  void unBind();
  void uniform1i(const char* uniformName, int data);
  void uniformMatrix4fv(const char *uniformName);
  ~Program();

};


#endif //MINECRAFTCLONE_PROGRAM_H

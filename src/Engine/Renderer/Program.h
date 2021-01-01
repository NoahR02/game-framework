#ifndef MINECRAFTCLONE_PROGRAM_H
#define MINECRAFTCLONE_PROGRAM_H

#include <vector>
#include "Shader.h"
#include <glm/glm.hpp>

struct Program {
  unsigned int rendererID;

  Program() = default;
  Program(std::vector<Shader> shaders);
  void bind();
  void unbind();
  void uniform1i(const char* uniformName, int data);
  void uniformMatrix4fv(const char *uniformName, glm::mat4 mat4);
  ~Program();
};


#endif //MINECRAFTCLONE_PROGRAM_H

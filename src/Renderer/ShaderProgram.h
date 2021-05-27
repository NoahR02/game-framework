#ifndef RPG_SHADERPROGRAM_H
#define RPG_SHADERPROGRAM_H


#include <string>
#include <glad/glad.h>

class ShaderProgram {

private:
  unsigned int rendererID;

public:
  ShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

  void setUniformMatrix4fv(const std::string& uniformName, int count = 1, bool transpose = false, const float* value = nullptr);
  void setUniform1i(const std::string& uniformName, int value = 0);
  void attachShader(const std::string& path, GLenum type);
  void bind();
  void unBind();

  ~ShaderProgram();

  void setUniform4f(const std::string &uniformName, float r, float g, float b, float a);
};


#endif //RPG_SHADERPROGRAM_H

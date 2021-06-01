#include <fstream>
#include "ReadFile.h"

std::string readFile(const std::string& path) {
  std::ifstream file {path, std::ios::in | std::ios::binary};
  if(file) return std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
  return "";
}
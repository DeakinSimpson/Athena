#pragma once

#include <glad/glad.h>

class Shader {
public:
  unsigned int sID {}; // shader program ID

  Shader() = default;

  void init(const char* vertexShaderSource, const char* fragmentShaderSource);

  void _delete() const;
};

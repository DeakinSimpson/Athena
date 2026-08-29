#pragma once

#include <glad/glad.h>
#include <string>

class Shader {
public:
  unsigned int sID {}; // shader program ID

  Shader() = default;

  void init(const char* vertexShaderSource, const char* fragmentShaderSource);

  void use();

  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;
  void setVec4(
      const std::string& name, float x, float y, float z, float w) const;

  void _delete() const;
};

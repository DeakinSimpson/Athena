#pragma once

#include <glad/glad.h>
#include "vbo.hpp"

class VAO {
public:
  unsigned int ID {};

  VAO();

  void linkAttribute(
      VBO& vbo, 
      unsigned int index, 
      int size, 
      GLenum type, 
      GLboolean normalized, 
      GLsizei stride, 
      const void* offset
  );

  void bind() const;
  void unbind() const;
  void _delete() const;
  
};

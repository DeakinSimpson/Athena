#pragma once

#include "glad/glad.h"

class VBO {
public:
  unsigned int ID {};

  /*
   * generates the VBO object and links it to the vertex data, adding verticies
   * to the buffer
   */
  VBO(const float* vertices, GLsizeiptr size);

  void bind() const;
  void unbind() const;
  void _delete() const;
};

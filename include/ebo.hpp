#pragma once

#include <glad/glad.h>

class EBO {
public:
  unsigned int ID {};

  EBO(const unsigned int* indices, GLsizeiptr size);

  void bind() const;
  void unbind() const;
  void _delete() const;
};

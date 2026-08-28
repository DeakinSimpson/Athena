#include "vbo.hpp"

#include <glad/glad.h>

VBO::VBO(float* vertices, GLsizeiptr size) {
  glGenBuffers(1, &ID);
  glBindBuffer(GL_ARRAY_BUFFER, ID);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::bind() const {
  glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::unbind() const {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::_delete() const {
  glDeleteBuffers(1, &ID);
}

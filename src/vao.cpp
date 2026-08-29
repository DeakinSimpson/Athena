#include "vao.hpp"

#include <glad/glad.h>

VAO::VAO() {
  glGenVertexArrays(1, &ID);
  bind();
}

void VAO::linkAttribute(
    VBO& vbo, 
    unsigned int index, 
    int size, 
    GLenum type, 
    GLboolean normalized, 
    GLsizei stride, 
    const void* offset
) {
  vbo.bind();
  glVertexAttribPointer(index, size, type, normalized, stride, offset);
  glEnableVertexAttribArray(index);
  vbo.unbind();
}

void VAO::bind() const {
  glBindVertexArray(ID);
}

void VAO::unbind() const {
  glBindVertexArray(0);
}

void VAO::_delete() const {
  glDeleteVertexArrays(1, &ID);
}
  


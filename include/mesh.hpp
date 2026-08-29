#pragma once

#include "vao.hpp"
#include "vbo.hpp"
#include "ebo.hpp"

class Mesh {
  const float* vertices_;
  const unsigned int* indices_;
  unsigned int texture_ {};
  
  VAO vao_;
  VBO vbo_;
  EBO ebo_;

public:
  Mesh(
      const float* vertices, GLsizeiptr verticesSize, 
      const unsigned int* indices, GLsizeiptr indicesSize

  );

  void setTexture(const char* texturePath);

  void onRender();
};

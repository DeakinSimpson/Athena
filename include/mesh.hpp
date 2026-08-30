#pragma once

#include "vao.hpp"
#include "vbo.hpp"
#include "ebo.hpp"
#include "texture.hpp"
#include "camera.hpp"

class Mesh {
  float* vertices_;
  unsigned int* indices_;
  Texture texture_ {};
  
  VAO vao_;
  VBO vbo_;
  EBO ebo_;

public:
  Mesh(
      float* vertices, GLsizeiptr verticesSize, 
      unsigned int* indices, GLsizeiptr indicesSize

  );

  void setTexture(const char* texturePath);

  void onRender(Camera* camera);
};

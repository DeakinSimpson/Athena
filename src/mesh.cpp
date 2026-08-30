#include "mesh.hpp"
#include "vao.hpp"
#include "shader.hpp"
#include <GLFW/glfw3.h>
#include <cmath>
#include <stb/stb_image.h>
#include "engineglobals.hpp"

/*
 * Initisialise the Mesh object, initialising the the vao vbo and ebo as well
 */
Mesh::Mesh(
    float* vertices, GLsizeiptr verticesSize,
    unsigned int* indices, GLsizeiptr indicesSize
) : vertices_(vertices)
  , indices_(indices)
  , vao_()
  , vbo_(vertices, verticesSize) 
  , ebo_(indices, indicesSize) {
    // TODO: update to use general inputs that match the input buffer for the 
    // mesh
    vao_.linkAttribute(vbo_, 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    vao_.linkAttribute(vbo_, 1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vao_.linkAttribute(vbo_, 2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    // TODO: verify that this is in the initialisation and not in the onRender()
    glBindVertexArray(vao_.ID);
      }

void Mesh::onRender() {
  
  EngineGlobals::shader_.use();

  double  timeValue = glfwGetTime();
  float greenValue = static_cast<float>(sin(timeValue) / 2.0 + 0.5);
  EngineGlobals::shader_.setVec4("ourColor", 0.0f, greenValue, 0.0f, 0.0f);

  glBindTexture(GL_TEXTURE_2D, texture_.get());

  // TODO: update to use general inputs, not just 6
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Mesh::setTexture(const char* texturePath) {
  texture_.init(texturePath);
}

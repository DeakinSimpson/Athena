#include "mesh.hpp"
#include "vao.hpp"
#include "shader.hpp"

/*
 * Initisialise the Mesh object, initialising the the vao vbo and ebo as well
 */
Mesh::Mesh(
    const float* vertices, GLsizeiptr verticesSize,
    const unsigned int* indices, GLsizeiptr indicesSize,
    Shader* shader
) : vertices_(vertices)
  , indices_(indices)
  , vao_()
  , vbo_(vertices, verticesSize) 
  , ebo_(indices, indicesSize) {

    // TODO: update to use general inputs that match the input buffer for the 
    // mesh
    vao_.linkAttribute(vbo_, 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // TODO: verify that this is in the initialisation and not in the onRender()
    glUseProgram(shader->sID);
  }

void Mesh::onRender() {
  // TODO: update to use general inputs, not just 6
  glBindVertexArray(vao_.ID);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

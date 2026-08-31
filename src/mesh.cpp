#include "mesh.hpp"
#include "vao.hpp"
#include "shader.hpp"
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include "engineglobals.hpp"
#include "camera.hpp"

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

  // get the aspect ratio using framebuffercallback
  int width;
  int height;
  glfwGetFramebufferSize(EngineGlobals::window_.get(), &width, &height);
  float aspectRatio { static_cast<float>(width) / static_cast<float>(height) };

  // get the projection matrix
  glm::mat4 projection { glm::perspective(
      glm::radians(EngineGlobals::camera_.zoom_),
      aspectRatio,
      EngineGlobals::d_cameraClipNear,
      EngineGlobals::d_cameraClipFar
      ) };

  // send the projection matrix to the shader
  EngineGlobals::shader_.setMat4("projection", projection);

  // get the viewpoer matrix
  glm::mat4 viewport { EngineGlobals::camera_.getViewMatrix() };

  // send the viewport matrix to the shader
  EngineGlobals::shader_.setMat4("viewport", viewport);

  //TODO: get the model matrix
  glm::mat4 model { glm::mat4(1.0f) };
    
  // set the send the model to the shader
  EngineGlobals::shader_.setMat4("model", model);

  glBindTexture(GL_TEXTURE_2D, texture_.get());

  // TODO: update to use general inputs, not just 6
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Mesh::setTexture(const char* texturePath) {
  texture_.init(texturePath);
}

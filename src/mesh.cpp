#include "mesh.hpp"
#include "vao.hpp"
#include "shader.hpp"
#include <GLFW/glfw3.h>
#include <cmath>
#include <stb/stb_image.h>
#include "engineglobals.hpp"
#include <iostream>

/*
 * Initisialise the Mesh object, initialising the the vao vbo and ebo as well
 */
Mesh::Mesh(
    const float* vertices, GLsizeiptr verticesSize,
    const unsigned int* indices, GLsizeiptr indicesSize
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

  glBindTexture(GL_TEXTURE_2D, texture_);

  // TODO: update to use general inputs, not just 6
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Mesh::setTexture(const char* texturePath) {
  // create texture and bind
  glGenTextures(1, &texture_);
  glBindTexture(GL_TEXTURE_2D, texture_);

  // set parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  // load texture
  // image files store rows top-to-bottom, but GL texture v=0 is the bottom,
  // so flip on load or the image renders upside down
  stbi_set_flip_vertically_on_load(true);

  int width, height, nrChannels;
  unsigned char *data = stbi_load(texturePath, &width, &height, &nrChannels, STBI_rgb);

  // verify texture loaded
  if (data) {
      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

      glTexImage2D(
          GL_TEXTURE_2D, 
          0, 
          GL_RGB, 
          width, 
          height, 
          0, 
          GL_RGB, 
          GL_UNSIGNED_BYTE, 
          data
      );
      glGenerateMipmap(GL_TEXTURE_2D);
  }
  else {
      std::cerr << "Failed to load texture" << std::endl;
  }

  // delete data
  stbi_image_free(data);
}

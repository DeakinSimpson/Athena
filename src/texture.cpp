#include "texture.hpp"
#include <glad/glad.h>
#include <iostream>
#include <stb/stb_image.h>

static void bindTexture(unsigned int& textureID);
static void setParameters();
static void loadTexture(const char* filepath);

/*
 * Sets the texture, places the texture in location 1
 */
void Texture::init(const char* filepath) {
  bindTexture(ID_);
  setParameters();
  loadTexture(filepath);
}

static void bindTexture(unsigned int& texture) {
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
}

/*
 * this sets the configurations for the texture itself and what it will look
 * like
 * GL_REPEAT: the texture repeats
 * GL_LINEAR: makes the image look pixelated rather then smooth
 */
static void setParameters() {
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

static void loadTexture(const char* filepath) {
  stbi_set_flip_vertically_on_load(true);
  // lkload texture into data
  int width, height, nrChannels;
  unsigned char* data = stbi_load(
      filepath, &width, &height, &nrChannels, STBI_rgb);

  // check if data loaded correctly, if so load into openGL
  if (data) {
    /* set the pixel alignment to 1, rather then the default value
     * this means that the "row" of pixels is just 1 pixel, this will mitigate
     * any misaligned images*/
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(
        GL_TEXTURE_2D, 0, GL_RGB, width, height, 
        0, GL_RGB, GL_UNSIGNED_BYTE, data
    );

    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cerr << "Failed to load texture: " << filepath << std::endl;
  }

  // delete data as it is already on the gpu
  stbi_image_free(data);
}



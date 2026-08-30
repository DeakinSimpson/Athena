#include "renderer.hpp"
#include <vector>

void Renderer::init() {

}

// loop through each mesh and render it
void Renderer::onRender() {
  for (size_t i {}; i < meshes_.size(); ++i) {
    meshes_[i]->onRender();  
  }
}

// add the reference to the mesh to the meshes vector
void Renderer::addMesh(Mesh* mesh) {
  meshes_.push_back(mesh); 
}



void Renderer::onDelete() {
  
}

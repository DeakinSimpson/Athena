#pragma once

#include <vector>
#include "mesh.hpp"

class Renderer {
  std::vector<Mesh*> meshes_ {}; // list of all mesh objects being rendered
  
public:
  Renderer() = default;

  void init();

  void onRender();

  void addMesh(Mesh* mesh);

  void onDelete();
};

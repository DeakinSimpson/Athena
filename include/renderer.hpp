#pragma once

#include <vector>
class Mesh; // this is forward decleration of mesh as it was making a loop

class Renderer {
  std::vector<Mesh*> meshes_ {}; // list of all mesh objects being rendered
  
public:
  Renderer() = default;

  void init();

  void onRender();

  void addMesh(Mesh* mesh);

  void onDelete();
};

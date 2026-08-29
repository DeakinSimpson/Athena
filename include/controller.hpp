#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Controller {
public:

  Controller() = default;

  void onUpdate();

private:

  void processInput();


};

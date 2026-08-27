#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "engine.hpp"

int main()
{
  Engine engine;

  engine.start();

  while (!glfwWindowShouldClose(engine.getWindow().get())) {
    engine.onUpdate();
  }

  engine.stop();

  return 0;
}

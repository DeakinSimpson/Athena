#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "engine.hpp"

int main()
{
  Engine engine;

  engine.start();
  engine.stop();

  return 0;
}

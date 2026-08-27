#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "window.hpp"

int main()
{
  Window window;

  window.init();

  while (!glfwWindowShouldClose(window.get())) {
    glfwSwapBuffers(window.get());
    glfwPollEvents();
  }

  return 0;
}



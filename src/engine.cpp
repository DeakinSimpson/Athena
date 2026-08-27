#include "engine.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void Engine::start() {
  // initialise the window
  window_.init();
}

void Engine::onUpdate() {
  glfwSwapBuffers(window_.get());
  glfwPollEvents();
}

void Engine::stop() {
  glfwTerminate();
}

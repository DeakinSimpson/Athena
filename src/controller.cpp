#include "controller.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

/*
 * Holds the logic of what needs to be updated each frame for the controller
 */
void Controller::onUpdate(GLFWwindow* window) {
  processInput(window);
}

/*
 * this uses glfw key callbacks to determine what key is being pressed, this
 * gets called each frame
 */
void Controller::processInput(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

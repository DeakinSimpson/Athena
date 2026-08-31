#include "controller.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "engineglobals.hpp"

/*
 * Holds the logic of what needs to be updated each frame for the controller
 */
void Controller::onUpdate(float deltaTime) {
  processInput(deltaTime);
}

/*
 * this uses glfw key callbacks to determine what key is being pressed, this
 * gets called each frame
 */
void Controller::processInput(float deltaTime) {
  GLFWwindow* window = EngineGlobals::window_.get();

  bool escPressed = glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS;
  if (escPressed && !escWasPressed_) {
    if (EngineGlobals::g_isInMenu) {
      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
      EngineGlobals::g_isInMenu = false;
    } else {
      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
      EngineGlobals::g_isInMenu = true;
    }
  }
  escWasPressed_ = escPressed;

  // controlls movement
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    EngineGlobals::camera_.ProcessKeyboard(FORWARD, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    EngineGlobals::camera_.ProcessKeyboard(BACKWARD, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    EngineGlobals::camera_.ProcessKeyboard(LEFT, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    EngineGlobals::camera_.ProcessKeyboard(RIGHT, deltaTime);
}

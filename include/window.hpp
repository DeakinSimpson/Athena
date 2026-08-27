#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
public:

  Window() = default;
  ~Window();

  // because -Werror=effc++, we must explicitly state what to do, i just delete
  Window(const Window&) = delete;
  Window& operator=(const Window&) = delete;

  void init();
  
  // returns the pointer to the GLFWwindow variable
  GLFWwindow* get() { return window_; }

private:
  GLFWwindow* window_;
};

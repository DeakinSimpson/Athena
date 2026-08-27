#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <default.hpp>

class Window {
public:

  Window() = default;
  void init();
  GLFWwindow* get() { return window_; }

private:
  GLFWwindow* window_;
};

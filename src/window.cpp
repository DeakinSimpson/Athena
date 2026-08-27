#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "window.hpp"
#include "default.hpp"
#include <iostream>

static void setWindowOptions();
static void checkGLFWwindowInit(GLFWwindow* window);
static void checkGladInit(GLFWwindow* window);
static void framebuffer_size_callback(GLFWwindow*, int width, int height); 

void Window::init() {
  setWindowOptions();
    
  // set the window object
  window_ = glfwCreateWindow(
    dv::DEFAULT_WINDOW_WIDTH, 
    dv::DEFAULT_WINDOW_HEIGHT, 
    dv::DEFAULT_WINDOW_NAME,
    NULL,
    NULL);

  // check for errors when creating the window object
  checkGLFWwindowInit(window_);

  // binds the current window to the cpu
  glfwMakeContextCurrent(window_);

  // check glad initialised
  checkGladInit(window_);

  // set the resizing callback to the custom callback
  glfwSetFramebufferSizeCallback(window_, framebuffer_size_callback);
}

// window deconstructor
Window::~Window() {
  glfwTerminate();
  glfwDestroyWindow(window_);
}

// sets the GLFW window options before launching
static void setWindowOptions() {
  glfwInit();
  // set the major and minor version
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  /*only use the core of OPENGL instead of using all the backwards compatible
  features */  
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

// checks if the window opened correctly
static void checkGLFWwindowInit(GLFWwindow* window) {
  if (window == NULL) {
    std::cerr << "Failed to create GLFW Window" << std::endl;
    glfwTerminate();
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }
}

static void checkGladInit(GLFWwindow* window) {
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "Failed to initialise GLAD" << std::endl;
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }
}

// resizes the glfw window to match the size fo the window
static void framebuffer_size_callback(GLFWwindow*, int width, int height) {
  glViewport(0, 0, width, height);
}

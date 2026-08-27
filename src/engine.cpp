#include "engine.hpp"
#include "controller.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// forward declerations for static functions
static void setBackgroundColor(
    const float r, 
    const float g, 
    const float b, 
    const float a
);

/*
 * constructer just calls init, this is to not clutter the constructor
 */
Engine::Engine() {
  init();
}

/* this initialises any objects that have a function that needs to be
 * tun in order for them to be functional
 */
void Engine::init() {
  // initialise the window
  window_.init();
}

/*
 * this holds the main render loop, all rendering logic goes here
 */
void Engine::start() {
  while (!glfwWindowShouldClose(window_.get())) {
    onUpdate();
    onRender();
  }
}

/*
 * This processes what needs to be updated each frame, this is different from
 * onRender() as it does not hold any of the rendering logic
 */
void Engine::onUpdate() {
  // process user input
  controller_.onUpdate(window_.get());

  glfwSwapBuffers(window_.get());
  glfwPollEvents();
}

/* 
 * this processes all render logic for the engine. it runs after the updated
 * logic and handles all on-screen drawing
 */
void Engine::onRender() {
  setBackgroundColor(0.2f, 0.3f, 0.3f, 1.0f);
}

/*
 * this is essentially just the deconstructor, however i wanted an explicit
 * stop funtion to make main easier to read
 */
void Engine::stop() {
  glfwTerminate();
}

static void setBackgroundColor(
    const float r,
    const float g,
    const float b,
    const float a
) {
  // sets the color state
  glClearColor(r, g, b, a);

  // this sets the color state
  glClear(GL_COLOR_BUFFER_BIT);

}

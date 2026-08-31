#include "engine.hpp"
#include "controller.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "mesh.hpp"
#include <optional> // temp
#include "engineglobals.hpp"
#include "fileReader.hpp"
#include "renderer.hpp"

// forward declerations for static functions
static void setBackgroundColor(
    const float r, 
    const float g, 
    const float b, 
    const float a
);

// TEMP TEST
float vertices[] = {
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
};

unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,  // first Triangle
    1, 2, 3   // second Triangle
};

#include <optional>


std::optional<Mesh> testMesh;

// ---------------------------------------------------------------------------

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
  EngineGlobals::window_.init();

  // generate shader_
  EngineGlobals::shader_.init(
      FileReader::readFile(EngineGlobals::vertexShaderLocation).c_str(),
      FileReader::readFile(EngineGlobals::fragmentShaderLocation).c_str());
  
  // initialize renderer
  EngineGlobals::g_renderer.init();

  EngineGlobals::camera_.init(
      EngineGlobals::d_position, 
      EngineGlobals::d_up, 
      EngineGlobals::d_yaw, 
      EngineGlobals::d_pitch);

  testMesh.emplace(
      vertices, sizeof(vertices), 
      indices, sizeof(indices));

  testMesh->setTexture("data/textures/GigaChad.jpg");

  EngineGlobals::g_renderer.addMesh(&*testMesh);
  
  EngineGlobals::debugGui_.init(EngineGlobals::window_.get());
}

/*
 * this holds the main render loop, all rendering logic goes here
 */
void Engine::start() {
  while (!glfwWindowShouldClose(EngineGlobals::window_.get())) {
    onUpdate();
    onRender();
  }
}

/*
 * This processes what needs to be updated each frame, this is different from
 * onRender() as it does not hold any of the rendering logic
 */
void Engine::onUpdate() {
  // get deltatime
  float currentFrame = static_cast<float>(glfwGetTime());
  float deltaTime = currentFrame - EngineGlobals::g_lastFrameTime;
  EngineGlobals::g_lastFrameTime = currentFrame;
  EngineGlobals::g_fps = static_cast<unsigned int>(1.0f / deltaTime);

  // process user input
  EngineGlobals::controller_.onUpdate(deltaTime);

  glfwPollEvents();
}

/* 
 * this processes all render logic for the engine. it runs after the updated
 * logic and handles all on-screen drawing
 */
void Engine::onRender() {
  EngineGlobals::debugGui_.startRenderLoop();

  setBackgroundColor(0.2f, 0.3f, 0.3f, 1.0f);

  EngineGlobals::g_renderer.onRender();

  EngineGlobals::debugGui_.endRenderLoop(EngineGlobals::window_.get(), EngineGlobals::g_fps);

  glfwSwapBuffers(EngineGlobals::window_.get());
}

/*
 * this is essentially just the deconstructor, however i wanted an explicit
 * stop funtion to make main easier to read
 */
void Engine::stop() {
  glfwTerminate();
  EngineGlobals::debugGui_.delete_();
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

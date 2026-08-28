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

// TEMP TEST
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

float vertices[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
};
unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,  // first Triangle
    1, 2, 3   // second Triangle
};

#include <optional>
#include "vao.hpp"
#include "vbo.hpp"
#include "ebo.hpp"

std::optional<VAO> vao;
std::optional<VBO> vbo;
std::optional<EBO> ebo;

// ---------------------------------------------------------------------------

/*
 * constructer just calls init, this is to not clutter the constructor
 */
Engine::Engine() : shader_{} { 
  init();
}

/* this initialises any objects that have a function that needs to be
 * tun in order for them to be functional
 */
void Engine::init() {
  // initialise the window
  window_.init();

  shader_.emplace(vertexShaderSource, fragmentShaderSource);

  // TEMP
  vao.emplace();
  vao->bind();

  vbo.emplace(vertices, static_cast<GLsizeiptr>(sizeof(vertices)));
  ebo.emplace(indices, static_cast<GLsizeiptr>(sizeof(indices)));

  vao->linkAttribute(*vbo, 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  // ----
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

  glfwPollEvents();
}

/* 
 * this processes all render logic for the engine. it runs after the updated
 * logic and handles all on-screen drawing
 */
void Engine::onRender() {
  setBackgroundColor(0.2f, 0.3f, 0.3f, 1.0f);

  glUseProgram(shader_->sID);
  glBindVertexArray(vao->ID);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  glfwSwapBuffers(window_.get());
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

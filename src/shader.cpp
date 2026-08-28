#include "shader.hpp"
#include <glad/glad.h>
#include <stddef.h> // used for NULL
#include <iostream>

// forward declared variables
static void compileVertexShader(const char* source, unsigned int& ID);
static void compileFragmentShader(const char* source, unsigned int& ID);
static void checkShaderCompileStatus(const unsigned int ID);
static void linkShaderProgram(
    unsigned int& shaderProgram,
    const unsigned int vertexShaderID,
    const unsigned int fragmentShaderID
); 

// compiles the shaderProgram
Shader::Shader(
    const char* vertexShaderSource, 
    const char* fragmentShaderSource
) {
  unsigned int vertexShader;
  unsigned int fragmentShader;

  compileVertexShader(vertexShaderSource, vertexShader);
  compileFragmentShader(fragmentShaderSource, fragmentShader);
  linkShaderProgram(sID, vertexShader, fragmentShader); 
}

/*
 * Compiles the vertex shader
 */
static void compileVertexShader(const char* source, unsigned int& ID) {
  ID = glCreateShader(GL_VERTEX_SHADER); // create vertex shader
  glShaderSource(ID, 1, &source, NULL);  // set the vertex shader source
  glCompileShader(ID);                   // compile the shader

  checkShaderCompileStatus(ID);
}

/*
 * Compiles the fragment shader
 */
static void compileFragmentShader(const char* source, unsigned int& ID) {
  ID = glCreateShader(GL_FRAGMENT_SHADER); // create vertex shader
  glShaderSource(ID, 1, &source, NULL);  // set the vertex shader source
  glCompileShader(ID);                   // compile the shader

  checkShaderCompileStatus(ID); 
}

/*
 * checks for compile errors when a shader is compiled
 */
static void checkShaderCompileStatus(const unsigned int ID) {
  int success;
  char infoLog[512];

  glGetShaderiv(ID, GL_COMPILE_STATUS, &success); // get the compile status

  if (!success) {
    glGetShaderInfoLog(ID, 512, NULL, infoLog);
    std::cerr << "Shader Failed to Compile\n" << infoLog << std::endl;
  }
}

/*
 * links the vertex and fragment shader into a single shader program
 */
static void linkShaderProgram(
    unsigned int& shaderProgram,
    const unsigned int vertexShaderID,
    const unsigned int fragmentShaderID
) {
  shaderProgram = glCreateProgram();                // create shaderProgram
  glAttachShader(shaderProgram, vertexShaderID);    // attach vertex shader
  glAttachShader(shaderProgram, fragmentShaderID);  // attach fragment shader
  glLinkProgram(shaderProgram);                     // link program together
  
  // check for linking errors
  int success;
  char infoLog[512];
  glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success); // get the compile status
  if (!success) {
    glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cerr << "Shader Failed to Compile\n" << infoLog << std::endl;
  }

  // cleanup vertex and fragment shader
  glDeleteShader(vertexShaderID);
  glDeleteShader(fragmentShaderID);
}

// cleanup program shader
void Shader::_delete() const {
  glDeleteProgram(sID);
}


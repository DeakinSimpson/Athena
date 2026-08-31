#include "shader.hpp"
#include <ext/matrix_float4x4.hpp>
#include <glad/glad.h>
#include <stddef.h> // used for NULL
#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// forward declared variables
static void compileVertexShader(const char* source, unsigned int& ID);
static void compileFragmentShader(const char* source, unsigned int& ID);
static void checkShaderCompileStatus(const unsigned int ID);
static void linkShaderProgram(
    unsigned int& shaderProgram,
    const unsigned int vertexShaderID,
    const unsigned int fragmentShaderID
); 

void Shader::init(
    const char* vertexShaderSource, 
    const char* fragmentShaderSource
    ) {
  unsigned int vertexShader;
  unsigned int fragmentShader;

  compileVertexShader(vertexShaderSource, vertexShader);
  compileFragmentShader(fragmentShaderSource, fragmentShader);
  linkShaderProgram(sID, vertexShader, fragmentShader); 
}

void Shader::use() {
  glUseProgram(sID);
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
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success); // get the link status
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cerr << "Shader Program Failed to Link\n" << infoLog << std::endl;
  }

  // cleanup vertex and fragment shader
  glDeleteShader(vertexShaderID);
  glDeleteShader(fragmentShaderID);
}

void Shader::setBool(const std::string &name, bool value) const {         
  glUniform1i(glGetUniformLocation(sID, name.c_str()), (int)value); 
}
void Shader::setInt(const std::string &name, int value) const { 
  glUniform1i(glGetUniformLocation(sID, name.c_str()), value); 
}
void Shader::setFloat(const std::string &name, float value) const { 
  glUniform1f(glGetUniformLocation(sID, name.c_str()), value); 
}
void Shader::setMat4(const std::string& name, const glm::mat4 value) const {  
  glUniformMatrix4fv(
      glGetUniformLocation(sID, name.c_str()), 
      1, 
      GL_FALSE, 
      glm::value_ptr(value)
  );
}
void Shader::setVec4(
    const std::string& name, 
    float x, 
    float y, 
    float z, 
    float w) const {
  glUniform4f(glGetUniformLocation(sID, name.c_str()), x, y, z, w);
}
// cleanup program shader
void Shader::_delete() const {
  glDeleteProgram(sID);
}




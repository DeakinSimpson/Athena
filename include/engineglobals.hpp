#pragma once

#include "window.hpp"
#include "controller.hpp"
#include "debuggui.hpp"
#include "shader.hpp"
#include <string>

namespace EngineGlobals {
  // to change to json file
  inline const std::string vertexShaderLocation { "data/shaders/original.vertshad" };
  inline const std::string fragmentShaderLocation { "data/shaders/original.fragshad" };
 

  inline Window window_ {};
  inline Controller controller_ {};
  inline Shader shader_ {}; 
  inline DebugGui debugGui_ {};

}

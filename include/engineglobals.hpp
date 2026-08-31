#pragma once

#include "window.hpp"
#include "controller.hpp"
#include "debuggui.hpp"
#include "shader.hpp"
#include <string>
#include "renderer.hpp"
#include <glm/glm.hpp>
#include "camera.hpp"

namespace EngineGlobals {
  // to change to json file
  inline const std::string vertexShaderLocation { "data/shaders/original.vertshad" };
  inline const std::string fragmentShaderLocation { "data/shaders/original.fragshad" };

  // default window variables
  inline unsigned int d_screenWidth { 800 };
  inline unsigned int d_screenHeight { 600 };

  inline Window window_ {};
  inline Controller controller_ {};
  inline Shader shader_ {}; 
  inline DebugGui debugGui_ {};
  inline Renderer g_renderer {};
  inline Camera camera_ {};

  // default camera variables
  inline const float d_yaw          { -90.0f };
  inline const float d_pitch        { 0.0f };
  inline const float d_speed        { 2.5f };
  inline const float d_sensitivity  { 0.1f };
  inline const float d_zoom         { 45.0f };
  inline const glm::vec3 d_up { 0.0f, 1.0f, 0.0f };
  inline const glm::vec3 d_front { 0.0f, 0.0f, -1.0f };
  inline const float d_cameraClipNear { 0.1f };
  inline const float d_cameraClipFar { 100.0f };
  inline const glm::vec3 d_position { 0.0f, 0.0f, 0.0f };

  // for debug menu
  inline bool g_isInMenu { false };
}

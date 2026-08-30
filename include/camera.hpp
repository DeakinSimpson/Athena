#pragma once

#include <glm/glm.hpp>
#include "engineglobals.hpp"

class Camera {
public:
  // camera Attributes
  glm::vec3 position_;
  glm::vec3 front_;
  glm::vec3 up_;
  glm::vec3 right_;
  glm::vec3 worldUp_;
  // euler Angles
  float yaw_;
  float pitch_;
  // camera options
  float movementSpeed_;
  float mouseSensitivity_;
  float zoom_; 

  Camera() = default;

  void init(glm::vec3 position,
      glm::vec3 up = EngineGlobals::d_up,
      float yaw = EngineGlobals::d_yaw, 
      float pitch = EngineGlobals::d_pitch);

  glm::mat4 getViewMatrix();

private:
  float lastX_;
float lastY_;
  bool firstMouse_ { true };

  void updateCameraVectors();
  void updateFrontVec();
};

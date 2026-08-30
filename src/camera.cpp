#include "camera.hpp"

#include "engineglobals.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

void Camera::init(glm::vec3 position, glm::vec3 up, float yaw, float pitch) {
  // set default camera values
  front_ = EngineGlobals::d_front;
  movementSpeed_ = EngineGlobals::d_speed;
  mouseSensitivity_ = EngineGlobals::d_sensitivity;
  zoom_ = EngineGlobals::d_zoom;

  // set mouse variables
  lastX_ = EngineGlobals::d_screenWidth / 2.0f; // centre of screen
  lastY_ = EngineGlobals::d_screenHeight / 2.0f;

  // set the input values
  position_ = position;
  worldUp_ = EngineGlobals::d_up;
  yaw_ = yaw;
  pitch_ = pitch;

  updateCameraVectors(); 
}

void Camera::updateCameraVectors() {
  updateFrontVec();
  right_ = glm::normalize(glm::cross(front_, worldUp_));
  up_ = glm::normalize(glm::cross(right_, front_));
}

// update the front vectors
void Camera::updateFrontVec() {
  glm::vec3 front;
  
  // get new front values
  front.x = cos(glm::radians(yaw_) * cos(glm::radians(pitch_))); 
  front.y = sin(glm::radians(pitch_));
  front.z = sin(glm::radians(yaw_) * cos(glm::radians(pitch_)));

  front_ = glm::normalize(front);
}

glm::mat4 Camera::getViewMatrix() {
  return glm::lookAt(position_, position_ + front_, up_);
}

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
  lastX_ = static_cast<float>(EngineGlobals::d_screenWidth) / 2.0f; // centre of screen
  lastY_ = static_cast<float>(EngineGlobals::d_screenHeight) / 2.0f;

  // set the input values
  position_ = position;
  worldUp_ = up;
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
  front.x = static_cast<float>(cos(glm::radians(yaw_)) * cos(glm::radians(pitch_)));
  front.y = static_cast<float>(sin(glm::radians(pitch_)));
  front.z = static_cast<float>(sin(glm::radians(yaw_)) * cos(glm::radians(pitch_)));

  front_ = glm::normalize(front);
}

glm::mat4 Camera::getViewMatrix() {
  return glm::lookAt(position_, position_ + front_, up_);
}

// processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
    float velocity = movementSpeed_ * deltaTime;
    if (direction == FORWARD)
        position_ += front_ * velocity;
    if (direction == BACKWARD)
        position_ -= front_ * velocity;
    if (direction == LEFT)
        position_ -= right_ * velocity;
    if (direction == RIGHT)
        position_ += right_ * velocity;
}

// processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
    xoffset *= EngineGlobals::d_sensitivity;
    yoffset *= EngineGlobals::d_sensitivity;

    yaw_   += xoffset;
    pitch_ += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (pitch_ > 89.0f)
            pitch_ = 89.0f;
        if (pitch_ < -89.0f)
            pitch_ = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}

// processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void Camera::ProcessMouseScroll(float yoffset)
{
    zoom_ -= (float)yoffset;
    if (zoom_ < 1.0f)
        zoom_ = 1.0f;
    if (zoom_ > 45.0f)
        zoom_ = 45.0f;
}

void Camera::handleMouseInput(float xpos, float ypos)
{
    if (firstMouse_) {
        lastX_ = xpos;
        lastY_ = ypos;
        firstMouse_ = false;
    }

    float xoffset = xpos - lastX_;
    float yoffset = lastY_ - ypos; 

    lastX_ = xpos;
    lastY_ = ypos;
    if (!EngineGlobals::g_isInMenu) {
      ProcessMouseMovement(xoffset, yoffset);
    }
}

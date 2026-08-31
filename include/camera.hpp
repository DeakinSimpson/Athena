#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN,
};

class Camera {
public:
  // camera Attributes
  glm::vec3 position_ {};
  glm::vec3 front_ {};
  glm::vec3 up_ {};
  glm::vec3 right_ {};
  glm::vec3 worldUp_ {};
  // euler Angles
  float yaw_ {};
  float pitch_ {};
  // camera options
  float movementSpeed_ {};
  float mouseSensitivity_ {};
  float zoom_ {};

  Camera() = default;

  void init(glm::vec3 position,
      glm::vec3 up,
      float yaw, 
      float pitch);

  glm::mat4 getViewMatrix();

  void ProcessKeyboard(Camera_Movement direction, float deltaTime);
  void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
  void ProcessMouseScroll(float yoffset);
  void handleMouseInput(float xpos, float ypos);

private:
  float lastX_ {};
  float lastY_ {};
  bool firstMouse_ { true };

  void updateCameraVectors();
  void updateFrontVec();
};

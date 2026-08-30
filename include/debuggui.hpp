#pragma once

// imgui/glm are vendor code, included -isystem via the Makefile so their
// internal warnings don't need suppressing here
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class DebugGui {
  bool isWireframeMode { false };
public:
  DebugGui() = default;

  void init(GLFWwindow* window) {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io { ImGui::GetIO() };
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;// Enable Keyboard Controls

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();   
  }

  void startRenderLoop() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    
  }

  void endRenderLoop(GLFWwindow* window) {
    ImGui::Text("Hello World!");

    // exit button
    if (ImGui::Button("Exit Engine"))
      glfwSetWindowShouldClose(window, true);

    // wireframe select
    if (ImGui::Button(isWireframeMode ? "WireFrame: ON" : "WireFrame: OFF")) {
      if (isWireframeMode) {
        isWireframeMode = !isWireframeMode;
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      } else {
        isWireframeMode = !isWireframeMode;
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      }
    }

    // testing -----------------------------
    glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
    vec = trans * vec;
    ImGui::Text("x: %f, y: %f, z: %f", vec.x, vec.y, vec.z);
    // -------------------------------------

    // render gui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }

  void delete_() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();   
  }

};


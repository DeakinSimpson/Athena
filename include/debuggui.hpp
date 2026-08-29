#pragma once

// getting errors due to vendor code
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#pragma GCC diagnostic pop

#include "GLFW/glfw3.h"

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


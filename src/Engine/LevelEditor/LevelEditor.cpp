#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>
#include "LevelEditor.h"
#include "../Renderer/FrameBuffer.h"

LevelEditor::LevelEditor(Window& window, FrameBuffer& frameBuffer) {
  this->window = &window;
  this->frameBuffer = &frameBuffer;
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
  io.ConfigDockingWithShift = true;
  const char* glsl_version = "#version 150";
  ImGui::StyleColorsDark();


  ImGui_ImplGlfw_InitForOpenGL(window.glfwWindow, true);
  ImGui_ImplOpenGL3_Init(glsl_version);
}

void LevelEditor::render() {
  ImGuiIO &io = ImGui::GetIO();

  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

  ImGui::BeginMainMenuBar();
  ImGui::Text("Menu");
  ImGui::EndMainMenuBar();

  bool p_open = true;
  ImGui::ShowMetricsWindow(&p_open);
  ImGui::ShowAboutWindow(&p_open);

  ImGui::Begin("Game", nullptr, ImGuiWindowFlags_NoScrollbar);
  ImGui::SetWindowSize(ImVec2(window->getWidth()/4, window->getHeight()/4));

  ImGui::Image((void*)frameBuffer->frameBufferTexture.rendererID,
               ImGui::GetContentRegionMax(),
               ImVec2(0, 1), ImVec2(1, 0));

  ImGui::End();


  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    GLFWwindow* backupContext = glfwGetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(backupContext);
  }

}

LevelEditor::~LevelEditor() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

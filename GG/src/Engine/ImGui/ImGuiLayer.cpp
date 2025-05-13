#include "ggpch.h"
#include "ImGuiLayer.h"

#include "Engine/Application.h"
#include "Platform/OpenGL/imgui_impl_opengl2.h"
#include "Platform/OpenGL/imgui_impl_glfw.h"

namespace GG {
  ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {

  }

  ImGuiLayer::~ImGuiLayer() {
    
  }

  void ImGuiLayer::OnAttach() {
    // 1. 创建 ImGui 上下文
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // 2. 配置样式
    ImGui::StyleColorsDark();  // 或者使用 ImGui::StyleColorsClassic();

    // 3. 设置平台 & 渲染器后端（这里以 OpenGL2 为例）
    ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow()), true);
    ImGui_ImplOpenGL2_Init();
  }

  void ImGuiLayer::OnDetach() {
    
  }

  void ImGuiLayer::OnUpdate() {
    // 1. 开始新帧
    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // 2. 显示 ImGui 自带的测试窗口
    static bool show_demo_window = true;
    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);

    // 3. 绘制所有界面
    ImGui::Render();
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
  }

  void ImGuiLayer::OnEvent(Event& e) {

  }
}
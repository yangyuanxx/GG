#include "ggpch.h"
#include "ImGuiLayer.h"

#include "Engine/Application.h"
#include "Platform/OpenGL/imgui_impl_opengl2.h"
#include "Platform/OpenGL/imgui_impl_glfw.h"

ImGuiKey ImGui_ImplGlfw_KeyToImGuiKey(int keycode, int scancode);

namespace GG
{
  ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer")
  {
  }

  ImGuiLayer::~ImGuiLayer()
  {
  }

  void ImGuiLayer::OnAttach()
  {
    // 1. 创建 ImGui 上下文
    ImGui::CreateContext();

    // 2. 配置样式
    ImGui::StyleColorsDark(); // 或者使用 ImGui::StyleColorsClassic();

    ImGuiIO &io = ImGui::GetIO();

    // 3. 设置平台 & 渲染器后端（这里以 OpenGL2 为例）
    ImGui_ImplGlfw_InitForOpenGL(
      (GLFWwindow *)Application::Get().GetWindow().GetNativeWindow(),
      false // 不安装回调，使用我们自己的事件系统
    );
    ImGui_ImplOpenGL2_Init();
  }

  void ImGuiLayer::OnDetach()
  {
  }

  void ImGuiLayer::OnUpdate()
  {
    Application &app = Application::Get();

    // 1. 开始新帧
    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplGlfw_NewFrame(); // 更新鼠标状态等
    ImGui::NewFrame();

    // ==== C++ tip ====
    // 函数内的 static 变量在程序运行期间一直存在，且只会初始化一次。
    // 这里必须是 static 的，否则每次 OnUpdate show_demo_window 都会被初始化为 true，
    // 从而导致这个测试窗口永远都关闭不了。
    // =================
    // 2. 显示 ImGui 自带的测试窗口
    static bool show_demo_window = true;
    if (show_demo_window)
      ImGui::ShowDemoWindow(&show_demo_window);

    // 3. 绘制所有界面
    ImGui::Render();
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
  }

  void ImGuiLayer::OnEvent(Event &e)
  {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(ImGuiLayer::OnMouseButtionPressedEvent));
    dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FN(ImGuiLayer::OnMouseButtionReleasedEvent));
    dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
    dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
    dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
    dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
    dispatcher.Dispatch<KeyTypedEvent>(BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
  }

  bool ImGuiLayer::OnMouseButtionPressedEvent(MouseButtonPressedEvent &e)
  {
    ImGuiIO &io = ImGui::GetIO();
    io.AddMouseButtonEvent(e.GetMouseButton(), true);
    return false;
  }

  bool ImGuiLayer::OnMouseButtionReleasedEvent(MouseButtonReleasedEvent &e)
  {
    ImGuiIO &io = ImGui::GetIO();
    io.AddMouseButtonEvent(e.GetMouseButton(), false);
    return false;
  }

  bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent &e)
  {
    ImGuiIO &io = ImGui::GetIO();
    io.AddMousePosEvent(e.GetX(), e.GetY());
    return false;
  }

  bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent &e)
  {
    ImGuiIO &io = ImGui::GetIO();
    io.AddMouseWheelEvent(e.GetXOffset(), e.GetYOffset());
    return false;
  }

  bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent &e)
  {
    ImGuiIO &io = ImGui::GetIO();
    io.AddKeyEvent(ImGui_ImplGlfw_KeyToImGuiKey(e.GetKeyCode(), e.GetKeyCode()), true);
    return false;
  }

  bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent &e)
  {
    ImGuiIO &io = ImGui::GetIO();
    io.AddKeyEvent(ImGui_ImplGlfw_KeyToImGuiKey(e.GetKeyCode(), e.GetKeyCode()), false);
    return false;
  }
  bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent &e)
  {
    ImGuiIO &io = ImGui::GetIO();
    io.AddInputCharacter(e.GetKeyCode());
    return false;
  }
  bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent &e)
  {
    return false;
  }
}
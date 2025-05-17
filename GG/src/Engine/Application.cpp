#include "Application.h"
#include "Log.h"
#include "Events/Event.h"
#include "ImGui/ImGuiLayer.h"
#include "Input.h"

#include <glad/glad.h>

namespace GG {

  Application* Application::s_Instance = nullptr;

  Application::Application() {
    GG_CORE_ASSERT(!s_Instance, "Application already exists!");
    s_Instance = this;

    m_Window = std::unique_ptr<Window>(Window::Create());
    m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

    // 仅现在 opengl 支持，mac 不再支持 opengl
    // unsigned int id;
    // glGenVertexArrays(1, &id);    
  }

  Application::~Application() {
  }

  void Application::PushLayer(Layer* layer) {
    m_LayerStack.PushLayer(layer);
    layer->OnAttach();
  }

  void Application::PushOverlay(Layer* layer) {
    m_LayerStack.PushOverlay(layer);
    layer->OnAttach();
  }

  void Application::OnEvent(Event& e) {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

    // 触发每一层(Layer)的 OnEvent 回调
    for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
      (*--it)->OnEvent(e);
      if (e.Handled)
        break;
    }
  }

  void Application::Run() {

    const GLubyte* version = glGetString(GL_VERSION);
    std::cout << "OpenGL Version: " << version << std::endl;

    // PushOverlay(new ImGuiLayer());

    while(m_Running) {
      // 设置清除颜色并清除缓冲区
      glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      // 触发每一层 Update 回调
      for(Layer* layer : m_LayerStack) {
        layer->OnUpdate();
      }

      m_Window->OnUpdate();
    }
  }

  bool Application::OnWindowClose(WindowCloseEvent& e) {
    m_Running = false;
    return true;
  }
}

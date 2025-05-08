#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"
#include "Events/Event.h"

#include <GLFW/glfw3.h>

namespace GG {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

  Application::Application() {
    m_Window = std::unique_ptr<Window>(Window::Create());
    m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
  }

  Application::~Application() {
  }

  void Application::OnEvent(Event& e) {
    GG_CORE_INFO("{0}", e.ToString());
  }

  void Application::Run() {
    while(m_Running) {
      // 设置清除颜色并清除缓冲区
      glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);
      m_Window->OnUpdate();
    }
  }
}

#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"

#include <GLFW/glfw3.h>

namespace GG {
  Application::Application() {
    m_Window = std::unique_ptr<Window>(Window::Create());
  }

  Application::~Application() {
  }

  void Application::Run() {
    glfwSwapInterval(1);
    bool isPink = true;
    while(m_Running) {
      // 设置清除颜色并清除缓冲区
      glClearColor(isPink ? 1.0f : 0.0f, 0.0f, isPink ? 1.0f : 0.0f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);
      m_Window->OnUpdate();
      isPink = !isPink;
    }
  }
}

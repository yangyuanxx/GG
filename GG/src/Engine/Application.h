#pragma once

// 苹果系统已逐步弃用 OpenGL，因此需要添加以下宏以禁用警告
#define GL_SILENCE_DEPRECATION

#include "Core.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"

namespace GG {
  class GG_API Application {
    public:
      Application();
      virtual ~Application();
      void Run();

      void OnEvent(Event& e);
    private:

      bool OnWindowClose(WindowCloseEvent& e);

      std::unique_ptr<Window> m_Window;
      bool m_Running = true;
  };

  // 由应用程序实现
  Application* CreateApplication();
}

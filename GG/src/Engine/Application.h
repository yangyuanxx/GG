#pragma once

// 苹果系统已逐步弃用 OpenGL，因此需要添加以下宏以禁用警告
#define GL_SILENCE_DEPRECATION

#include "Core.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"
#include "Layer.h"
#include "LayerStack.h"

namespace GG {
  class GG_API Application {
    public:
      Application();
      virtual ~Application();
      void Run();

      void OnEvent(Event& e);

      void PushLayer(Layer* layer);
      void PushOverlay(Layer* layer);

      inline Window& GetWindow() { return *m_Window; };
      static Application& Get() { return *s_Instance; };
      
    private:

      bool OnWindowClose(WindowCloseEvent& e);

      std::unique_ptr<Window> m_Window;
      
      bool m_Running = true;
      LayerStack m_LayerStack;

      static Application* s_Instance;
  };

  // 显式的 extern 表示该函数是外部定义的（由应用程序实现）
  extern Application* CreateApplication();
}

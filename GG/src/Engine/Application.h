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

      // ==== C++ tip ====
      // static 成员函数不需要实例化，可以直接通过类名调用，
      // 例如 Application::Get()
      // =================
      static Application& Get() { return *s_Instance; };
      
    private:

      bool OnWindowClose(WindowCloseEvent& e);

      std::unique_ptr<Window> m_Window;
      
      bool m_Running = true;
      LayerStack m_LayerStack;

      // ==== C++ tip ====
      // static 成员变量不需要实例化，可以直接通过类名访问，
      // 例如 Application::s_Instance
      // =================
      static Application* s_Instance;
  };

  // ==== C++ tip ====
  // 实际上不用显式写出 extern，因为 C++ 默认就是 extern。
  // 显式的 extern 只是为了提升可读性，即表示这个函数的定义在别的地方
  // =================
  // 该函数由用户实现
  extern Application* CreateApplication();
}

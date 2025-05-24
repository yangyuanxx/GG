#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"
#include "Layer.h"
#include "LayerStack.h"
#include "ImGui/ImGuiLayer.h"
#include "Renderer/Shader.h"

namespace GG {
  class Application {
    public:
      Application();
      virtual ~Application();
      void Run();

      void OnEvent(Event& e);

      void PushLayer(Layer* layer);
      void PushOverlay(Layer* layer);

      inline Window& GetWindow() { return *m_Window; };

      // C++ tip
      // static 成员函数不需要实例化，可以直接通过类名调用，
      // 例如 Application::Get()
      // ____
      static Application& Get() { return *s_Instance; };
      
    private:

      bool OnWindowClose(WindowCloseEvent& e);

      std::unique_ptr<Window> m_Window;
      ImGuiLayer* m_ImGuiLayer;
      
      bool m_Running = true;
      LayerStack m_LayerStack;

      unsigned int m_VertexArray;   // VAO
      unsigned int m_VertexBuffer;  // VBO
      unsigned int m_IndexBuffer;   // IBO/EBO      
      std::unique_ptr<Shader> m_Shader;

    private:
      // C++ tip
      // static 成员变量不需要实例化，可以直接通过类名访问，
      // 例如 Application::s_Instance
      // ____
      static Application* s_Instance;
  };

  // C++ tip
  // 实际上不用显式写出 extern，因为 C++ 默认就是 extern。
  // 显式的 extern 只是为了提升可读性，即表示这个函数的定义在别的地方
  // ____
  // 该函数由用户实现
  extern Application* CreateApplication();
}

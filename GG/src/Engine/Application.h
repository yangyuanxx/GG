#pragma once

// 苹果系统已逐步弃用 OpenGL，因此需要添加以下宏以禁用警告
#define GL_SILENCE_DEPRECATION

#include "Core.h"
#include "Events/Event.h"

#include <GLFW/glfw3.h>

namespace GG {
  class GG_API Application {
    public:
      Application();
      virtual ~Application();
      void Run();
    private:
      GLFWwindow* m_Window = nullptr;
  };

  // 由应用程序实现
  Application* CreateApplication();
}

#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"

#include <GLFW/glfw3.h>

namespace GG {
  Application::Application() {
    // 初始化 GLFW
    if (!glfwInit()) {
        GG_CORE_ERROR("Failed to initialize GLFW");
        return;
    }

    // 设置 OpenGL 版本（可选）
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 创建窗口
    m_Window = glfwCreateWindow(800, 600, "Pink Window", NULL, NULL);
    if (!m_Window) {
        GG_CORE_ERROR("Failed to create GLFW window");
        glfwTerminate();
        return;
    }

    // 设置当前上下文
    glfwMakeContextCurrent(m_Window);
  }

  Application::~Application() {
    if (m_Window) {
      glfwDestroyWindow(m_Window);
    }
    glfwTerminate();
  }

  void Application::Run() {
    volatile bool running = true;
    glClearColor(1.0f, 0.5f, 0.5f, 1.0f); // 粉色

    while(running) {
      // 清除颜色缓冲区
      glClear(GL_COLOR_BUFFER_BIT);

      // 交换缓冲区
      glfwSwapBuffers(m_Window);

      // 处理事件
      glfwPollEvents();
    }
  }
}

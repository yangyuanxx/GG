#include "ggpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace GG
{
  OpenGLContext::OpenGLContext(GLFWwindow *windowHandle)
      : m_WindowHandle(windowHandle)
  {
    GG_CORE_ASSERT(windowHandle, "Window handle is null.");
  }

  void OpenGLContext::Init()
  {
    glfwMakeContextCurrent(m_WindowHandle);
    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    GG_CORE_ASSERT(status, "Failed to initialize Glad.");

    GG_CORE_INFO("OpenGL Info:");
    GG_CORE_INFO("  Vendor: {0}", (const char *)glGetString(GL_VENDOR));
    GG_CORE_INFO("  Renderer: {0}", (const char *)glGetString(GL_RENDERER));
    GG_CORE_INFO("  Version: {0}", (const char *)glGetString(GL_VERSION));
  }

  void OpenGLContext::SwapBuffers()
  {
    // 交换缓冲区，当开启垂直同步时，会等待 vsync 信号
    glfwSwapBuffers(m_WindowHandle);
  }
}
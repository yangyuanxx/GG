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
  }

  void OpenGLContext::SwapBuffers()
  {
    // 交换缓冲区，当开启垂直同步时，会等待 vsync 信号
    glfwSwapBuffers(m_WindowHandle);
  }
}
#pragma once
#include "Engine/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace GG {
  class OpenGLContext : public GraphicsContext {
    public:
      OpenGLContext(GLFWwindow* windowHandle);
      virtual void Init() override;
      virtual void SwapBuffers() override;
    private:
      GLFWwindow* m_WindowHandle;
  };
}
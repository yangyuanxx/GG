#include "ggpch.h"
#include "MacWindow.h"
#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Events/KeyEvent.h"
#include "Engine/Events/MouseEvent.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include "GLFW/glfw3.h"
#include <glad/glad.h>

namespace GG
{

  static bool s_GLFWInitialized = false;

  Window *Window::Create(const WindowProps &props)
  {
    return new MacWindow(props);
  }

  MacWindow::MacWindow(const WindowProps &props)
  {
    Init(props);
  }

  MacWindow::~MacWindow()
  {
    Shutdown();
  }

  void MacWindow::Init(const WindowProps &props)
  {
    m_Data.Title = props.Title;
    m_Data.Width = props.Width;
    m_Data.Height = props.Height;


    if (!s_GLFWInitialized)
    {
      // TODO: glfwTerminate on shutdown
      int success = glfwInit();
      GG_CORE_ASSERT(success, "Could not initialize GLFW!");
      s_GLFWInitialized = true;
    }

    // 苹果最高支持到 OpenGL 4.1
    const char *glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    m_NativeWindow = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);

    m_Context = new OpenGLContext(m_NativeWindow);
    m_Context->Init();

    glfwSetWindowUserPointer(m_NativeWindow, &m_Data);
    SetVSync(true);

    // Set GLFW callbacks
    glfwSetWindowSizeCallback(m_NativeWindow, [](GLFWwindow *window, int width, int height) {
      WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
      data.Width = width;
      data.Height = height;

      WindowResizeEvent event(width, height);
      data.EventCallback(event);
    });

    glfwSetWindowCloseCallback(m_NativeWindow, [](GLFWwindow *window) {
      WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
      WindowCloseEvent event;
      data.EventCallback(event);
    });

    glfwSetKeyCallback(m_NativeWindow, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
      WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
      switch (action) {
        case GLFW_PRESS: {
          KeyPressedEvent event(key, 0);
          data.EventCallback(event);
          break;
        }
        case GLFW_RELEASE: {
          KeyReleasedEvent event(key);
          data.EventCallback(event);
          break;
        }
        case GLFW_REPEAT: {
          KeyPressedEvent event(key, 1);
          data.EventCallback(event);
          break;
        }
      }
    });

    glfwSetMouseButtonCallback(m_NativeWindow, [](GLFWwindow *window, int button, int action, int mods) {
      WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
      switch (action) {
        case GLFW_PRESS: {
          MouseButtonPressedEvent event(button);
          data.EventCallback(event);
          break;
        }
        case GLFW_RELEASE: {
          MouseButtonReleasedEvent event(button);
          data.EventCallback(event);
          break;
        }
      }
    });

    glfwSetScrollCallback(m_NativeWindow, [](GLFWwindow *window, double xOffset, double yOffset) {
      WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
      MouseScrolledEvent event((float)xOffset, (float)yOffset);
      data.EventCallback(event);
    });

    glfwSetCursorPosCallback(m_NativeWindow, [](GLFWwindow *window, double xPos, double yPos) {
      WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
      MouseMovedEvent event((float)xPos, (float)yPos);
      data.EventCallback(event);
    });

    glfwSetCharCallback(m_NativeWindow, [](GLFWwindow *window, unsigned int codepoint) {
      WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
      KeyTypedEvent event(codepoint);
      data.EventCallback(event);
    });
  }

  void MacWindow::Shutdown()
  {
    glfwDestroyWindow(m_NativeWindow);
  }

  void MacWindow::OnUpdate()
  {
    glfwPollEvents();
    m_Context->SwapBuffers();
  }

  void MacWindow::SetVSync(bool enabled)
  {
    if (enabled)
      glfwSwapInterval(1);
    else
      glfwSwapInterval(0);
    m_Data.VSync = enabled;
  }

  bool MacWindow::IsVSync() const
  {
    return m_Data.VSync;
  }

}
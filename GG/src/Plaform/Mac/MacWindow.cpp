#include "ggpch.h"
#include "MacWindow.h"
#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Events/KeyEvent.h"
#include "Engine/Events/MouseEvent.h"

namespace GG {

  static bool s_GLFWInitialized = false;

  Window* Window::Create(const WindowProps& props) {
    return new MacWindow(props);
  }

  MacWindow::MacWindow(const WindowProps& props) {
    Init(props);
  }

  MacWindow::~MacWindow() {
    Shutdown();
  }

  void MacWindow::Init(const WindowProps& props) {
    m_Data.Title = props.Title;
    m_Data.Width = props.Width;
    m_Data.Height = props.Height;
    GG_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);
    if (!s_GLFWInitialized) {
      // TODO: glfwTerminate on shutdown
      int success = glfwInit();
      GG_CORE_ASSERT(success, "Could not initialize GLFW!");
      s_GLFWInitialized = true;
    }
    m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(m_Window);
    glfwSetWindowUserPointer(m_Window, &m_Data);
    SetVSync(true);

    // Set GLFW callbacks
    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
      WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
      data.Width = width;
      data.Height = height;

      WindowResizeEvent event(width, height);
      data.EventCallback(event);
    });

    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
      WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
      WindowCloseEvent event;
      data.EventCallback(event);
    });

    glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
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

    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
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

    glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
      WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
      MouseScrolledEvent event((float)xOffset, (float)yOffset);
      data.EventCallback(event);
    });
    
    glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {
      WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
      MouseMovedEvent event((float)xPos, (float)yPos);
      data.EventCallback(event);
    });
  }

  void MacWindow::Shutdown() {
    glfwDestroyWindow(m_Window);
  }

  void MacWindow::OnUpdate() {
    glfwPollEvents();

    // 交换缓冲区，当开启垂直同步时，会等待 vsync 信号
    glfwSwapBuffers(m_Window);
  }

  void MacWindow::SetVSync(bool enabled) {
    if (enabled)
      glfwSwapInterval(1);
    else
      glfwSwapInterval(0);
    m_Data.VSync = enabled;
  }

  bool MacWindow::IsVSync() const {
    return m_Data.VSync;
  }

}
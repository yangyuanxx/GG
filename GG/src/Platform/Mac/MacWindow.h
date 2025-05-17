#pragma once

#include "Engine/Window.h"

#include <GLFW/glfw3.h>

namespace GG {

  class MacWindow : public Window {

    public:
      MacWindow(const WindowProps& props);
      virtual ~MacWindow();

      void OnUpdate() override;

      inline unsigned int GetWidth() const override { return m_Data.Width; }
      inline unsigned int GetHeight() const override { return m_Data.Height; }

      inline void* GetNativeWindow() const override { return m_Window; }

      // Window attributes
      inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
      void SetVSync(bool enabled) override;
      bool IsVSync() const override;
    
    private:
      virtual void Init(const WindowProps& props);
      virtual void Shutdown();

    private:
      GLFWwindow* m_Window;

      struct WindowData {
        std::string Title;
        unsigned int Width, Height;
        bool VSync;
        EventCallbackFn EventCallback;
      };

      WindowData m_Data;

  };

}
#pragma once

#include "ggpch.h"

#include "Engine/Core.h"
#include "Engine/Events/Event.h"

namespace GG {
  struct WindowProps {
    std::string Title;
    unsigned int Width;
    unsigned int Height;

    WindowProps(const std::string& title = "GG Engine",
                unsigned int width = 1280,
                unsigned int height = 720)
      : Title(title), Width(width), Height(height) {}
  };

  class GG_API Window {
    public:
      using EventCallbackFn = std::function<void(Event&)>;
      
      virtual ~Window() {}

      virtual void OnUpdate() = 0;

      virtual unsigned int GetWidth() const = 0;
      virtual unsigned int GetHeight() const = 0;

      virtual void* GetNativeWindow() const = 0; // 返回 void*，让子类返回具体类型

      // Window attributes
      virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
      virtual void SetVSync(bool enabled) = 0;
      virtual bool IsVSync() const = 0;

      static Window* Create(const WindowProps& props = WindowProps());
  };
}
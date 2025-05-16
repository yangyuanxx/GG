#pragma once

#include "Engine/Layer.h"
#include "Engine/Core.h"
#include "Engine/Events/MouseEvent.h"
#include "Engine/Events/KeyEvent.h"
#include "Engine/Events/ApplicationEvent.h"

namespace GG {
  class GG_API ImGuiLayer : public Layer {
    public:
      ImGuiLayer();
      ~ImGuiLayer();

      void OnAttach();
      void OnDetach();
      void OnUpdate();
      void OnEvent(Event& event);
    private:
      bool OnMouseButtionPressedEvent(MouseButtonPressedEvent& e);
      bool OnMouseButtionReleasedEvent(MouseButtonReleasedEvent& e);
      bool OnMouseMovedEvent(MouseMovedEvent& e);
      bool OnMouseScrolledEvent(MouseScrolledEvent& e);
      bool OnKeyPressedEvent(KeyPressedEvent& e);
      bool OnKeyReleasedEvent(KeyReleasedEvent& e);
      bool OnKeyTypedEvent(KeyTypedEvent& e);
      bool OnWindowResizeEvent(WindowResizeEvent& e);
    private:
      float m_Time = 0.0f;
  };
}
#pragma once

#include "Engine/Layer.h"
#include "Engine/Core.h"
#include "Engine/Events/MouseEvent.h"
#include "Engine/Events/KeyEvent.h"
#include "Engine/Events/ApplicationEvent.h"

namespace GG {
  class ImGuiLayer : public Layer {
    public:
      ImGuiLayer();
      ~ImGuiLayer();

      virtual void OnAttach() override;
      virtual void OnDetach() override;
      virtual void OnImGuiRender() override;

      void Begin();
      void End();
    private:
      float m_Time = 0.0f;
  };
}
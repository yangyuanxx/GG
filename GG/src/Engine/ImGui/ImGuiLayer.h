#pragma once

#include "Engine/Layer.h"
#include "Engine/Core.h"

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

  };
}
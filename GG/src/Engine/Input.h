#pragma once
#include "Engine/Core.h"
#include "Events/Event.h"

namespace GG {
  class GG_API Input {
    public:
      // 通过这种方式，我们使得 static 方法变成 "virtual" 的
      inline static bool IsKeyPressed(int keycode) {
        return s_Instance->IsKeyPressedImpl(keycode);
      };
      inline static bool IsMouseButtonPressed(int button) {
        return s_Instance->IsMouseButtonPressedImpl(button);
      };
      inline static std::pair<float, float> GetMousePos() {
        return s_Instance->GetMousePosImpl();
      }
      inline static bool GetMousePosX() {
        return s_Instance->GetMousePosXImpl();
      }
      inline static bool GetMousePosY() {
        return s_Instance->GetMousePosYImpl();
      }
    protected:
      // ==== C++ tip ====
      // virtual xxx = 0 表示一个纯虚函数，即必须在子类中实现
      // vitrual xxx {} 表示一个普通虚函数，子类可以选择实现或不实现
      // =================
      virtual bool IsKeyPressedImpl(int keycode) = 0;
      virtual bool IsMouseButtonPressedImpl(int button) = 0;
      virtual std::pair<float, float> GetMousePosImpl() = 0;
      virtual float GetMousePosXImpl() = 0;
      virtual float GetMousePosYImpl() = 0;
    private:
      static Input* s_Instance;
  };
}
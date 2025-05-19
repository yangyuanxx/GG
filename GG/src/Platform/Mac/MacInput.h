#pragma once

#include "Engine/Input.h"

namespace GG
{
  class MacInput : public Input
  {
  protected:
    // C++ tip
    // override 关键词不是必须的，但为了可读性和自动检测，建议加上
    // ____
    virtual bool IsKeyPressedImpl(int keycode) override;
    virtual bool IsMouseButtonPressedImpl(int button) override;
    virtual std::pair<float, float> GetMousePosImpl() override;
    virtual float GetMousePosXImpl() override;
    virtual float GetMousePosYImpl() override;
  };
}
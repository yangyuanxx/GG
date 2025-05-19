#include "ggpch.h"
#include "MacInput.h"
#include "GLFW/glfw3.h"
#include "Engine/Application.h"

namespace GG
{

  Input *Input::s_Instance = new MacInput();

  bool MacInput::IsKeyPressedImpl(int keycode)
  {
    Application &app = Application::Get();
    auto nativeWindow = static_cast<GLFWwindow *>(app.GetWindow().GetNativeWindow());

    auto state = glfwGetKey(nativeWindow, keycode);
    return state == GLFW_PRESS || state == GLFW_REPEAT;
  }

  bool MacInput::IsMouseButtonPressedImpl(int button)
  {
    Application &app = Application::Get();
    auto nativeWindow = static_cast<GLFWwindow *>(app.GetWindow().GetNativeWindow());

    auto state = glfwGetMouseButton(nativeWindow, button);
    return state == GLFW_PRESS;
  }

  std::pair<float, float> MacInput::GetMousePosImpl()
  {
    Application &app = Application::Get();
    auto nativeWindow = static_cast<GLFWwindow *>(app.GetWindow().GetNativeWindow());

    double xpos, ypos;
    glfwGetCursorPos(nativeWindow, &xpos, &ypos);
    return std::pair<float, float>(xpos, ypos);
  }

  float MacInput::GetMousePosXImpl()
  {
    auto [x, y] = GetMousePos();
    return x;
  }

  float MacInput::GetMousePosYImpl()
  {
    auto [x, y] = GetMousePos();
    return y;
  }

}
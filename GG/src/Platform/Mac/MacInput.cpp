#include "ggpch.h"
#include "MacInput.h"
#include "GLFW/glfw3.h"
#include "Engine/Application.h"

namespace GG {

  Input* Input::s_Instance = new MacInput();

  bool MacInput::IsKeyPressedImpl(int keycode)
  {
    auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
    auto state = glfwGetKey(window, keycode);
    return state == GLFW_PRESS || state == GLFW_REPEAT;
  }

  bool MacInput::IsMouseButtonPressedImpl(int button)
  {
    auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
    auto state = glfwGetMouseButton(window, button);
    return state == GLFW_PRESS;
  }

  std::pair<float, float> MacInput::GetMousePosImpl()
  {
    auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
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
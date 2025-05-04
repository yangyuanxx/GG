#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"

namespace GG {
  Application::Application() {
  }

  Application::~Application() {
  }

  void Application::Run() {
    // 在栈上创建一个 WindowResizeEvent 对象
    WindowResizeEvent e(1280, 720);
    GG_TRACE(e.ToString());

    volatile bool running = true;
    while(running);
  }
}

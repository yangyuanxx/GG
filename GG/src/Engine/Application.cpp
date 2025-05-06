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
    if  (e.IsInCategory(EventCategory::EventCategoryApplication)) {
      GG_TRACE(e.ToString());
    }
    if (e.IsInCategory(EventCategory::EventCategoryInput)) {
      GG_TRACE(e.ToString());
    }

    volatile bool running = true;
    while(running);
  }
}

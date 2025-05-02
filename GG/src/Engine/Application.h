#pragma once
#include "Core.h"

namespace GG {
  class GG_API Application {
    public:
      Application();
      virtual ~Application();
      void Run();
  };

  // 由应用程序实现
  Application* CreateApplication();
}

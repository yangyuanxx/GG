#include "Application.h"
#include <stdio.h>

namespace GG {
  Application::Application() {
  }

  Application::~Application() {
  }

  void Application::Run() {
    printf("Run\n");
    while(true);
  }
}

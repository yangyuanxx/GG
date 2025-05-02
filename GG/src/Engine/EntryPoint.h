#pragma once
#include "Engine/Application.h"

// 声明，由应用程序实现
extern GG::Application* GG::CreateApplication();

int main(int argc, char** argv) {
  auto app = GG::CreateApplication();
  app->Run();
  delete app;
  return 0;
}
#pragma once
#include "Engine/Application.h"
#include <stdio.h>

// 声明，由应用程序实现
extern GG::Application* GG::CreateApplication();

int main(int argc, char** argv) {
  
  GG::Log::Init();
  GG_CORE_WARN("Initialized Log!");
  int a = 5;
  GG_INFO("Hello! Var={0}", a);

  auto app = GG::CreateApplication();
  app->Run();
  delete app;
  return 0;
}
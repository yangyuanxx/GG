#include <GG.h>
#include <stdio.h>

class Sandbox : public GG::Application {
  public:
    Sandbox() {
      printf("Sandbox start\n");
    }
    ~Sandbox() {
      printf("Sandbox end\n");
    }
};

GG::Application* GG::CreateApplication() {
  return new Sandbox();
}
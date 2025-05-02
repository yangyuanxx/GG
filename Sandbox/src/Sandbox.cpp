#include <GG.h>
#include <stdio.h>

class Sandbox : public GG::Application {
  public:
    Sandbox() {
      printf("Sandbox\n");
    }
    ~Sandbox() {
    }
};

GG::Application* GG::CreateApplication() {
  return new Sandbox();
}
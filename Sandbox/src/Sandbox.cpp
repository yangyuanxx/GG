#include <GG.h>
#include <stdio.h>

class ExampleLayer : public GG::Layer {
  public:
    ExampleLayer(): Layer("Example") {}

    void OnUpdate() override {
      GG_INFO("ExampleLayer::Update");
    }

    void OnEvent(GG::Event& event) override {
      GG_TRACE("{0}", event.ToString());
    }
};

class Sandbox : public GG::Application {
  public:
    Sandbox() {
      PushLayer(new ExampleLayer());
    }
    ~Sandbox() {
      printf("Sandbox end\n");
    }
};

GG::Application* GG::CreateApplication() {
  return new Sandbox();
}
#include <GG.h>
#include "imgui.h"

class ExampleLayer : public GG::Layer {
  public:
    ExampleLayer(): Layer("Example") {
    }

    void OnUpdate() override {
      if (GG::Input::IsKeyPressed(GG_KEY_TAB)) {
        GG_INFO("Tab key is pressed!");
      }
    }

    void OnEvent(GG::Event& event) override {
      // GG_TRACE("{0}", event.ToString());
    }

    virtual void OnImGuiRender() override {
      ImGui::Begin("Hello");
      ImGui::Text("Hello, world!");
      ImGui::End();
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
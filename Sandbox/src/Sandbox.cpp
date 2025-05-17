#include <GG.h>

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
#include "Application.h"
#include "Log.h"
#include "Events/Event.h"
#include "ImGui/ImGuiLayer.h"
#include "Input.h"

#include <glad/glad.h>

namespace GG {

  Application* Application::s_Instance = nullptr;

  Application::Application() {
    GG_CORE_ASSERT(!s_Instance, "Application already exists!");
    s_Instance = this;

    m_Window = std::unique_ptr<Window>(Window::Create());
    m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

    m_ImGuiLayer = new ImGuiLayer();
    PushOverlay(m_ImGuiLayer);

    // Vertex Array
    glGenVertexArrays(1, &m_VertexArray);
    glBindVertexArray(m_VertexArray);

    float vertices[3*3] = {
      -0.5f, -0.5f, 0.0f,
       0.5f, -0.5f, 0.0f,
       0.0f,  0.5f, 0.0f
    };

    m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

    unsigned int indices[3] = {0, 1, 2};
    m_IndexBuffer.reset(IndexBuffer::Create(indices, 3));

    // ========== 着色器程序 ==========
    // 顶点着色器
    const char* vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;

        out vec3 vPos;
        void main() {
            vPos = aPos;
            gl_Position = vec4(aPos, 1.0);
        }
    )";

    // 片段着色器
    const char* fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;
        in vec3 vPos;

        void main() {
            FragColor = vec4(vPos * 0.5 + 0.5, 1.0);
        }
    )";

    // 编译着色器
    m_Shader.reset(new Shader(vertexShaderSource, fragmentShaderSource));

  }

  Application::~Application() {
  }

  void Application::PushLayer(Layer* layer) {
    m_LayerStack.PushLayer(layer);
    layer->OnAttach();
  }

  void Application::PushOverlay(Layer* layer) {
    m_LayerStack.PushOverlay(layer);
    layer->OnAttach();
  }

  void Application::OnEvent(Event& e) {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

    // 触发每一层(Layer)的 OnEvent 回调
    for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
      (*--it)->OnEvent(e);
      if (e.Handled)
        break;
    }
  }

  void Application::Run() {
    while (m_Running)
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 绑定着色器程序
        m_Shader->Bind();

        glBindVertexArray(m_VertexArray);
        glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

        // 触发每一层 Update 回调
        for(Layer* layer : m_LayerStack) {
          layer->OnUpdate();
        }

        m_ImGuiLayer->Begin();
        for (Layer* layer : m_LayerStack) {
          layer->OnImGuiRender();
        }
        m_ImGuiLayer->End();

        m_Window->OnUpdate();
    }
  }

  bool Application::OnWindowClose(WindowCloseEvent& e) {
    m_Running = false;
    return true;
  }
}
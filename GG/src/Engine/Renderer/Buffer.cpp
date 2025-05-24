#include "ggpch.h"
#include "Buffer.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace GG {
   VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) {
    switch (Renderer::GetAPI()){
      case RendererAPI::None:
        GG_CORE_ASSERT(false, "RendererAPI::None is not supported.");
        return nullptr;
      case RendererAPI::OpenGL:
        return new OpenGLVertexBuffer(vertices, size);

      GG_CORE_ASSERT(false, "Unknown RendererAPI.");
      return nullptr;
    }
   }

   IndexBuffer* IndexBuffer::Create(uint32_t* vertices, uint32_t count) {
    switch (Renderer::GetAPI()){
      case RendererAPI::None:
        GG_CORE_ASSERT(false, "RendererAPI::None is not supported.");
        return nullptr;
      case RendererAPI::OpenGL:
        return new OpenGLIndexBuffer(vertices, count);

      GG_CORE_ASSERT(false, "Unknown RendererAPI.");
      return nullptr;
    }
   }
}
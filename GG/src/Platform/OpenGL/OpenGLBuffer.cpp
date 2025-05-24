#include "ggpch.h"
#include "OpenGLBuffer.h"
#include <glad/glad.h>

namespace GG
{

  ////////////////////////////////////////////////
  // VertexBuffer ////////////////////////////////
  ////////////////////////////////////////////////

  OpenGLVertexBuffer::OpenGLVertexBuffer(float *vertices, uint32_t size)
  {
    glGenBuffers(1, &m_RendererID); // 生成缓冲区对象
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID); // 绑定到目标
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
  }

  OpenGLVertexBuffer::~OpenGLVertexBuffer()
  {
    glDeleteBuffers(1, &m_RendererID);
  }

  void OpenGLVertexBuffer::Bind() const
  {
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID); // 绑定到目标
  }

  void OpenGLVertexBuffer::Unbind() const
  {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }



  ////////////////////////////////////////////////
  // IndexBufffer ////////////////////////////////
  ////////////////////////////////////////////////

  OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
    : m_Count(count)
  {
    glGenBuffers(1, &m_RendererID); // 生成缓冲区对象
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID); // 绑定到目标
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
  }

  OpenGLIndexBuffer::~OpenGLIndexBuffer()
  {
    glDeleteBuffers(1, &m_RendererID);
  }

  void OpenGLIndexBuffer::Bind() const
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID); // 绑定到目标
  }

  void OpenGLIndexBuffer::Unbind() const
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }

}
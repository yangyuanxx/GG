#pragma once

namespace GG
{

  class VertexBuffer
  {
  public:
    virtual ~VertexBuffer() {}

    // c++ tip:
    // 函数名后面的 const 表示，改方法承若不修改类实例的状态
    // ____
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    static VertexBuffer *Create(float *vertices, uint32_t size);
  };

  class IndexBuffer
  {
  public:
    virtual ~IndexBuffer() {}

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual uint32_t GetCount() const = 0;

    static IndexBuffer *Create(uint32_t *indices, uint32_t count);
  };

}
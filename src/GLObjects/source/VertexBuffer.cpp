#include "ErrorMacros.h"
#include <VertexBuffer.h>

namespace GlLibrary {
VertexBuffer::VertexBuffer(const void* buffer, int size)
{
    // Buffers in OpenGL are just buffers with bytes we specify
    GlCall(glGenBuffers(1, &m_vertexBufferId));

    Bind();
    // Reserve memory in Buffer, you will need to specify bytes.
    // using manual calculation due to working with stack and heap arrays
    GlCall(glBufferData(GL_ARRAY_BUFFER, size, buffer, GL_STATIC_DRAW));
}

void VertexBuffer::Bind() const
{

    // this will get you n ids for n number of buffers
    GlCall(glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId));
}
void VertexBuffer::Unbind() const
{

    GlCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
VertexBuffer::~VertexBuffer()
{
    GlCall(glDeleteBuffers(1, &m_vertexBufferId));
}
}

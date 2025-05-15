#include "MainWindow.h"
#include "VertexBufferLayout.h"
#include <VertexBuffer.h>

namespace GlLibrary {
VertexBuffer::VertexBuffer(const void* buffer, int size)
{
    // Buffers in OpenGL are just buffers with bytes we specify
    glGenBuffers(1, &m_vertexBufferId);

    Bind();
    // Reserve memory in Buffer, you will need to specify bytes.
    // using manual calculation due to working with stack and heap arrays
    glBufferData(GL_ARRAY_BUFFER, size, buffer, GL_STATIC_DRAW);
}

void VertexBuffer::Bind() const
{

    // this will get you n ids for n number of buffers
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
}

void addLayout(VertexBufferLayout& layout)
{
    const std::vector<VertexAttribParams>& vecAttribs = layout.getVertexAttribParams();
    uint64_t curPointer = 0;
    for (int i = 0; i < vecAttribs.size(); ++i) {
        const VertexAttribParams param = vecAttribs[i];
        glVertexAttribPointer(i, param.count, param.type, param.normalized, layout.getStride(), (void*)curPointer);
        curPointer += param.memSize;
    }
}

void enableAttribute(unsigned int index)
{
    glEnableVertexAttribArray(index);
}
void VertexBuffer::Unbind() const
{

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_vertexBufferId);
}
}

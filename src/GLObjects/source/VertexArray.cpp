#include "VertexArray.h"
#include "ErrorMacros.h"
#include "VertexBuffer.h"

namespace GlLibrary {
VertexArray::VertexArray()
{
    GlCall(glGenVertexArrays(1, &m_vaoId));
    GlCall(glBindVertexArray(m_vaoId));
}

void VertexArray::addBuffer(VertexBuffer& buffer, const VertexBufferLayout& layout)
{
    Bind();
    buffer.Bind();
    const std::vector<VertexAttribParams>& vecAttribs = layout.getVertexAttribParams();
    uint64_t curPointer = 0;
    for (int i = 0; i < vecAttribs.size(); ++i) {
        const VertexAttribParams param = vecAttribs[i];
        enableAttribute(i);
        GlCall(glVertexAttribPointer(i, param.count, param.type, param.normalized, layout.getStride(), (void*)curPointer));
        curPointer += param.memSize;
    }
}
void VertexArray::enableAttribute(unsigned int index)
{
    GlCall(glEnableVertexAttribArray(index));
}
void VertexArray::Bind()
{
    GlCall(glBindVertexArray(m_vaoId));
}

void VertexArray::Unbind()
{
    GlCall(glBindVertexArray(0));
}

}

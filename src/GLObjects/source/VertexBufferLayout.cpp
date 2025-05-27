#include "VertexBufferLayout.h"

namespace GlLibrary {
const std::vector<VertexAttribParams>& VertexBufferLayout::getVertexAttribParams() const
{
    return m_vertexAttribParams;
}

unsigned int VertexBufferLayout::getStride() const
{
    return m_stride;
}
}

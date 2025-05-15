#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#endif
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

#include "VertexShader.h"

namespace GlLibrary {
VertexShader::VertexShader()
{
    m_shaderId = glCreateShader(GL_VERTEX_SHADER);
}
} // namespace GlLibrary

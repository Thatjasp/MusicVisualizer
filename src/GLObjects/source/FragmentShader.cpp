#include "FragmentShader.h"

namespace GlLibrary {
FragmentShader::FragmentShader()
{
    m_shaderId = glCreateShader(GL_FRAGMENT_SHADER);
}
} // namespace GlLibrary

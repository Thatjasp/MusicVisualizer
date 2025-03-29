#include "ShaderProgram.h"

namespace GlLibrary {
ShaderProgram::ShaderProgram()
{
    m_shaderProgramID = glCreateProgram();
}

void ShaderProgram::attachShader(Shader& shader)
{
    glAttachShader(m_shaderProgramID, shader.getShaderId());
}
void ShaderProgram::linkShader()
{
    glLinkProgram(m_shaderProgramID);
}

GLuint ShaderProgram::shaderProgramId()
{
    return m_shaderProgramID;
}
} // namespace GlLibrary

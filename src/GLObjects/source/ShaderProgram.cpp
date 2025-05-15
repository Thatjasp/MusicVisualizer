#include "ShaderProgram.h"
#include "Shader.h"
#include <utility>

namespace GlLibrary {
ShaderProgram::ShaderProgram()
{
    m_shaderProgramID = glCreateProgram();
}
ShaderProgram::ShaderProgram(ShaderProgram&& other)
    : m_shaderProgramID(std::exchange(other.m_shaderProgramID, 0))
{
}

ShaderProgram& ShaderProgram::operator=(ShaderProgram&& other)
{
    std::swap(m_shaderProgramID, other.m_shaderProgramID);
    return *this;
}
void ShaderProgram::attachShader(Shader& shader)
{
    glAttachShader(m_shaderProgramID, shader.getShaderId());
}
void ShaderProgram::linkShader()
{
    glLinkProgram(m_shaderProgramID);
}

void ShaderProgram::validateProgram()
{
    glValidateProgram(m_shaderProgramID);
}

GLuint ShaderProgram::shaderProgramId()
{
    return m_shaderProgramID;
}
void ShaderProgram::useProgram()
{
    glUseProgram(m_shaderProgramID);
}
ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(m_shaderProgramID);
}

} // namespace GlLibrary

#include "ShaderProgram.h"
#include "ErrorMacros.h"
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
    GlCall(glAttachShader(m_shaderProgramID, shader.getShaderId()));
}
void ShaderProgram::linkShader()
{
    GlCall(glLinkProgram(m_shaderProgramID));
}

void ShaderProgram::validateProgram()
{
    GlCall(glValidateProgram(m_shaderProgramID));
}

GLuint ShaderProgram::shaderProgramId()
{
    return m_shaderProgramID;
}
void ShaderProgram::useProgram()
{
    GlCall(glUseProgram(m_shaderProgramID));
}
ShaderProgram::~ShaderProgram()
{
    GlCall(glDeleteProgram(m_shaderProgramID));
}

} // namespace GlLibrary

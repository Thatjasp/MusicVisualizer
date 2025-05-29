#include "ShaderProgram.h"
#include "ErrorMacros.h"
#include "MainWindow.h"
#include "Shader.h"
#include <iostream>
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

void ShaderProgram::addUniformLocation(std::string name)
{
    if (m_nameToLocation.contains(name)) {
        return;
    }
    int location = glGetUniformLocation(m_shaderProgramID, name.c_str());
    if (location == GL_INVALID_VALUE || location == GL_INVALID_OPERATION) {
        std::cerr << name << " Uniform location has caused an error" << std::endl;
        return;
    }
    m_nameToLocation[name] = location;
}

void ShaderProgram::setUniformLocation4f(std::string name, float v1, float v2, float v3, float v4)
{
    if (!m_nameToLocation.contains(name)) {
        std::cerr << name << " Not Found in nameTolocation map" << std::endl;
        return;
    }
    glUniform4f(m_nameToLocation[name], v1, v2, v3, v4);
}
} // namespace GlLibrary

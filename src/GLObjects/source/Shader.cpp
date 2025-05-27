#include "Shader.h"
#include "ErrorMacros.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <utility>

namespace GlLibrary {
Shader::Shader(Shader&& other)
    : m_shaderId(std::exchange(other.m_shaderId, 0))
{
}
Shader& Shader::operator=(Shader&& other)
{
    std::swap(m_shaderId, other.m_shaderId);
    return *this;
}
void Shader::addShaderSource(std::string sourceCodeStr)
{
    const char* sourceCode = sourceCodeStr.c_str();
    GlCall(glShaderSource(m_shaderId, 1, &sourceCode, NULL));
}

void Shader::addShaderSourceFile(std::filesystem::path sourceCodePath)
{
    addShaderSource(getSourceFileStr(sourceCodePath));
}

void Shader::addShaderSourceFile(
    std::vector<std::filesystem::path> vecSrcPaths)
{
    std::vector<std::string> srcCodeVec(vecSrcPaths.size());
    for (int i = 0; i < vecSrcPaths.size(); ++i) {
        srcCodeVec[i] = getSourceFileStr(vecSrcPaths[i]);
    }
    std::vector<const char*> srcCodeCharVec(vecSrcPaths.size());
    std::ranges::transform(
        srcCodeVec, std::back_inserter(srcCodeCharVec),
        [](std::string& str) -> const char* { return str.c_str(); });
    GlCall(glShaderSource(m_shaderId, srcCodeCharVec.size(), srcCodeCharVec.data(),
        NULL));
}

void Shader::compileShader()
{
    GlCall(glCompileShader(m_shaderId));
    // TODO: Error Handling
    GLint result;
    // i = wants an integer
    // v = wants a vector/array
    GlCall(glGetShaderiv(m_shaderId, GL_COMPILE_STATUS, &result));

    if (result == GL_FALSE) {
        int length;
        GlCall(glGetShaderiv(m_shaderId, GL_INFO_LOG_LENGTH, &length));
        char* str = (char*)alloca(length * sizeof(char));
        GlCall(glGetShaderInfoLog(m_shaderId, length, &length, str));
        std::cerr << std::string(str) << std::endl;
    }
}

std::string Shader::getSourceFileStr(std::filesystem::path path)
{
    std::ifstream sourceFileStream(path.string());
    std::stringstream ss;
    sourceFileStream.close();
    return ss.str();
}
GLuint Shader::getShaderId()
{
    return m_shaderId;
}
Shader::~Shader()
{
    glDeleteShader(m_shaderId);
}

} // namespace GlLibrary

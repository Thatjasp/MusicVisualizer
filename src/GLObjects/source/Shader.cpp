#include "Shader.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iterator>

namespace GlLibrary {
void Shader::addShaderSource(std::string sourceCodeStr)
{
    const char* sourceCode = sourceCodeStr.c_str();
    glShaderSource(m_shaderId, 1, &sourceCode, NULL);
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
    glShaderSource(m_shaderId, srcCodeCharVec.size(), srcCodeCharVec.data(),
        NULL);
}

void Shader::compileShader() { glCompileShader(m_shaderId); }

std::string Shader::getSourceFileStr(std::filesystem::path path)
{
    std::ifstream sourceFileStream(path.string());
    std::stringstream ss;
    ss << sourceFileStream.rdbuf();
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

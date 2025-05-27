#include "ShaderManager.h"
#include "FragmentShader.h"
#include "VertexShader.h"
#include <fstream>

#include <iostream>
#include <sstream>

namespace GlLibrary {
void ShaderManager::importShaders(std::filesystem::path path)
{
    enum ShaderType {
        VertexShader = 0,
        FragmentShader = 1,
        InvalidShader
    };

    std::ifstream sourceFileStream(path.string());
    std::stringstream ss[2];
    std::string line;
    ShaderType currentShaderEnum;
    while (std::getline(sourceFileStream, line)) {
        if (line.find("#shader vertex") != std::string::npos) {
            currentShaderEnum = ShaderType::VertexShader;
            continue;
        } else if (line.find("#shader fragment") != std::string::npos) {
            currentShaderEnum = ShaderType::FragmentShader;
            continue;
        }

        if (currentShaderEnum != InvalidShader) {
            ss[currentShaderEnum] << line << "\n";
        }
    }
    sourceFileStream.close();

    m_vertexShader.addShaderSource(ss[ShaderType::VertexShader].str());
    m_fragmentShader.addShaderSource(ss[ShaderType::FragmentShader].str());
}
void ShaderManager::compileShaders()
{
    m_vertexShader.compileShader();
    m_fragmentShader.compileShader();
}

FragmentShader& ShaderManager::getFragmentShader()
{
    return m_fragmentShader;
}

VertexShader& ShaderManager::getVertexShader()
{
    return m_vertexShader;
}

}

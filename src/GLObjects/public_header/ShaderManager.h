#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H
#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#endif
#include "FragmentShader.h"
#include "VertexShader.h"
#include <filesystem>

namespace GlLibrary {
class ShaderManager {
public:
    void importShaders(std::filesystem::path path);
    // TODO: Rule of 5
    FragmentShader& getFragmentShader();
    VertexShader& getVertexShader();
    void compileShaders();

private:
    FragmentShader m_fragmentShader;
    VertexShader m_vertexShader;
};
}
#endif

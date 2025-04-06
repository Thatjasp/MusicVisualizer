#ifndef SHADER_GL_CLASS
#define SHADER_GL_CLASS

#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#endif

#include <filesystem>
#include <vector>

namespace GlLibrary {

class Shader {
public:
    void addShaderSource(std::string);
    void addShaderSourceFile(std::filesystem::path);
    void addShaderSourceFile(std::vector<std::filesystem::path>);
    void compileShader();
    GLuint getShaderId();
    ~Shader();

protected:
    std::string getSourceFileStr(std::filesystem::path path);
    GLuint m_shaderId;
};
} // namespace GlLibrary
#endif

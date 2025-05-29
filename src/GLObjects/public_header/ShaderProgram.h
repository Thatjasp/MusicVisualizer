#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <unordered_map>
#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#endif

#include "Shader.h"

namespace GlLibrary {
class ShaderProgram {
public:
    ShaderProgram();
    ShaderProgram(const ShaderProgram&) = delete;
    ShaderProgram& operator=(ShaderProgram&) = delete;

    ShaderProgram(ShaderProgram&& other);
    ShaderProgram& operator=(ShaderProgram&& other);
    void attachShader(Shader& shader);
    void linkShader();
    void validateProgram();
    void useProgram();
    void setUniformLocation4f(std::string name, float v1, float v2, float v3, float v4);
    void addUniformLocation(std::string name);
    GLuint shaderProgramId();
    ~ShaderProgram();

private:
    std::unordered_map<std::string, int> m_nameToLocation;
    GLuint m_shaderProgramID;
};
} // namespace GlLibrary

#endif

#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

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
    void attachShader(Shader& shader);
    void linkShader();
    void validateProgram();
    void useProgram();
    GLuint shaderProgramId();

private:
    GLuint m_shaderProgramID;
};
} // namespace GlLibrary

#endif

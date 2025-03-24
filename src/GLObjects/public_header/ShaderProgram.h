#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#endif
#include "Shader.h"

namespace GlLibrary {
class ShaderProgram {
  void attachShader(Shader shader);
  void linkShader();

private:
  GLuint m_shaderProgramID;
};
} // namespace GlLibrary

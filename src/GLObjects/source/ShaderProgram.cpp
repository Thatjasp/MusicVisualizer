#include "ShaderProgram.h"

namespace GlLibrary {
void ShaderProgram::attachShader(Shader shader) {
  glAttachShader(m_shaderProgramID, shader.getShaderId());
}
void ShaderProgram::linkShader() { glLinkProgram(m_shaderProgramID); }
} // namespace GlLibrary

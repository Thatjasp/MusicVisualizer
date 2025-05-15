#ifndef VERTEX_ARRAY_CLASS
#define VERTEX_ARRAY_CLASS
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#endif

namespace GlLibrary {
class VertexArray {
public:
    VertexArray();
    void addBuffer(VertexBuffer& buffer, const VertexBufferLayout layout);
    void Bind();
    void Unbind();

private:
    GLuint vaoId;
};
}

#endif

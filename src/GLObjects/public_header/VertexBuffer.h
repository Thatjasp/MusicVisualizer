#ifndef VERTEX_BUFFER_CLASS
#define VERTEX_BUFFER_CLASS

#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#endif

#include "VertexBufferLayout.h"
namespace GlLibrary {
class VertexBuffer {
public:
    // TODO: Rule of 5
    // TODO: Figure out a way for the object to take care of the deletion potentially RAII
    VertexBuffer(const void* buffer, int size);

    void addLayout(VertexBufferLayout& layout);
    void enableAttribute(unsigned int index);

    void Bind() const;
    void Unbind() const;

    ~VertexBuffer();

private:
    GLuint m_vertexBufferId;
};
}

#endif

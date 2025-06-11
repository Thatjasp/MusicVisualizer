#ifndef INDEX_BUFFER_CLASS
#define INDEX_BUFFER_CLASS

#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#endif

namespace GlLibrary {
class IndexBuffer {
public:
    // TODO: Rule of 5
    IndexBuffer(const GLuint* buffer, unsigned int count);

    IndexBuffer(const IndexBuffer&) = delete;
    IndexBuffer& operator=(const IndexBuffer& other) = delete;

    IndexBuffer(IndexBuffer&& other);
    IndexBuffer& operator=(IndexBuffer&& other);

    void Bind() const;
    void Unbind() const;

    unsigned int getCount() const;

    ~IndexBuffer();

private:
    GLuint m_indexBufferId;
    unsigned int m_count;
};

}

#endif

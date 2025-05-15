#include <IndexBuffer.h>

namespace GlLibrary {
IndexBuffer::IndexBuffer(const GLuint* buffer, unsigned int count)
    : m_count(count)
{
    glGenBuffers(1, &m_indexBufferId);
    Bind();
    // THIS ASSUMES THAT UNSIGNED INT IS THE SAME AS GLuint
    // BE CAREFUL FOR ERRORS
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), buffer, GL_STATIC_DRAW);
}

void IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId);
}

void IndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int IndexBuffer::getCount() const
{
    return m_count;
}
IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_indexBufferId);
}

}

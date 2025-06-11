#include <ErrorMacros.h>
#include <IndexBuffer.h>
#include <utility>

namespace GlLibrary {
IndexBuffer::IndexBuffer(const GLuint* buffer, unsigned int count)
    : m_count(count)
{
    GlCall(glGenBuffers(1, &m_indexBufferId));
    Bind();
    // THIS ASSUMES THAT UNSIGNED INT IS THE SAME AS GLuint
    // BE CAREFUL FOR ERRORS
    GlCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), buffer, GL_STATIC_DRAW));
}
IndexBuffer::IndexBuffer(IndexBuffer&& other)
    : m_indexBufferId(std::exchange(other.m_indexBufferId, 0))
    , m_count(std::exchange(other.m_count, 0))
{
}
IndexBuffer& IndexBuffer::operator=(IndexBuffer&& other)
{
    std::swap(m_indexBufferId, other.m_indexBufferId);
    std::swap(m_count, other.m_count);
    return *this;
}

void IndexBuffer::Bind() const
{
    GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId));
}

void IndexBuffer::Unbind() const
{
    GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

unsigned int IndexBuffer::getCount() const
{
    return m_count;
}
IndexBuffer::~IndexBuffer()
{
    GlCall(glDeleteBuffers(1, &m_indexBufferId));
}

}

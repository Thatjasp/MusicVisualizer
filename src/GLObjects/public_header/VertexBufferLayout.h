#ifndef VERTEX_BUFFER_LAYOUT_CLASS
#define VERTEX_BUFFER_LAYOUT_CLASS
#include "MainWindow.h"
#include <vector>

#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#endif

namespace {
template <typename T>
concept GlType = requires(T num) {
    { num } -> std::unsigned_integral;
} || std::same_as<T, float>;
}
namespace GlLibrary {
struct VertexAttribParams {
    unsigned int count;
    GLenum type;
    GLboolean normalized;
    unsigned int memSize;
};

class VertexBufferLayout {
public:
    // TODO: This could be setup in a more streamline way
    // Potentially having more of parallel arrays structure
    // Its fine for now
    template <::GlType T>
    void addVertexAttribParams(unsigned int count)
    {
        // TODO: Unnecessary templating clean up code
        // (It was fun to use concepts tho)
        if constexpr (std::is_same<T, float>::value) {
            m_vertexAttribParams.push_back({ count, GL_FLOAT, GL_FALSE, count * 4 });
            m_stride += count * 4;
        } else if constexpr (std::is_same<T, GLuint>::value) {
            m_vertexAttribParams.push_back({ count, GL_UNSIGNED_INT, GL_FALSE, count * 4 });
            m_stride += count * 4;
        } else if constexpr (std::is_same<T, GLubyte>::value) {
            m_vertexAttribParams.push_back({ count, GL_UNSIGNED_BYTE, GL_FALSE, count * 1 });
            m_stride += count * 1;
        }
    }
    const std::vector<VertexAttribParams>& getVertexAttribParams() const;
    unsigned int getStride() const;

private:
    unsigned int m_stride;
    std::vector<VertexAttribParams> m_vertexAttribParams;
};
}

#endif

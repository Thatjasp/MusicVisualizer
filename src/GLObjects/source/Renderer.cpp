#include "Renderer.h"
#include "ErrorMacros.h"
namespace GlLibrary {
void Renderer::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}
void Renderer::Draw(VertexArray& va, IndexBuffer& ib, ShaderProgram& sp)
{
    Clear();
    sp.useProgram();
    va.Bind();
    ib.Bind();
    GlCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
}
}

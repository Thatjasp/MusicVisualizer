#pragma once

#include "IndexBuffer.h"
#include "ShaderProgram.h"
#include "VertexArray.h"
namespace GlLibrary {
class Renderer {
public:
    void Clear();
    void Draw(VertexArray& va, IndexBuffer& ib, ShaderProgram& sp);
};
}

#include "Texture.h"
#include "stb_image.h"

namespace GlLibrary {
Texture::Texture(const std::string& imagePath)
    : m_imagePath(imagePath)
{
    glGenTextures(1, &m_textureRendererId);
    glBindTexture(GL_TEXTURE_2D, m_textureRendererId);
    stbi_set_flip_vertically_on_load(1);

    m_imageBuffer = stbi_load(m_imagePath.c_str(), &m_Width, &m_Height, &m_BPP, 4);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Horizontal - S
    // If Bigger horizontally then it will Clamp instead of runoff
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    // Vertical - T
    // If Bigger vertically then it will Clamp instead of runoff
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    // Internal Format = format of how opengl will store the data
    // External Format = The format of the data you are PROVIDING
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_imageBuffer);
    Unbind();
}

void Texture::Bind(int slot) const
{
}
void Texture::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

int Texture::getWidth() const
{
    return m_Width;
}
int Texture::getHeight() const
{
    return m_Height;
}

Texture::~Texture()
{
}

}

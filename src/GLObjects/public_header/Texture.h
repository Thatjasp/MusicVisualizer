#pragma once
#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#endif
#include <string>
namespace GlLibrary {
class Texture {
public:
    Texture(const std::string& imagePath);

    void Bind(int slot = 0) const;
    void Unbind() const;

    int getWidth() const;
    int getHeight() const;

    ~Texture();

private:
    std::string m_imagePath;
    unsigned char* m_imageBuffer;
    GLuint m_textureRendererId;
    int m_Width;
    int m_Height;
    // Bytes per Pixel
    int m_BPP;
};
}

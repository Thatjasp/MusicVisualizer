#ifndef WINDOW_GL_H
#define WINDOW_GL_H

#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#endif

#include <string>

namespace GlLibrary {
class WindowGl {
public:
    WindowGl(int width, int height, std::string title,
        GLFWmonitor* monitor = NULL, GLFWwindow* share = NULL);

    WindowGl(const WindowGl& other);

    GLFWwindow* getRawPointer();
    void makeContextCurrent();
    void swapBuffer();
    bool windowShouldClose();
    void viewPortArea(int x, int y, int width, int height);

    int getWidth() const;
    int getHeight() const;
    int getX() const;
    int getY() const;

    WindowGl& operator=(const WindowGl& other);

    std::string getTitle() const;
    ~WindowGl();

private:
    GLFWwindow* mp_window;
    int m_width;
    int m_height;
    int m_x;
    int m_y;
    std::string m_title;
};

} // namespace GlLibrary
#endif

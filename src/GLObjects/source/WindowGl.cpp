#include "WindowGl.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include <utility>
namespace GlLibrary {

WindowGl::WindowGl(int width, int height, std::string title,
    GLFWmonitor* monitor, GLFWwindow* share)
{
    // Initialize GL Window
    glfwInit();

    // Type Hints for Glfw to understand what version it should use
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    mp_window = glfwCreateWindow(800, 800, "Bruhhhh", NULL, NULL);

    // If window isn't made then terminate
    if (mp_window == NULL) {
        glfwTerminate();
        return;
    }
    makeContextCurrent();
    glfwSwapInterval(1);
    // init glew
    if (glewInit() != GLEW_OK) {
        std::cerr << "Wack" << std::endl;
        glfwTerminate();
    }
}

WindowGl::WindowGl(WindowGl&& other) noexcept
    : mp_window(std::exchange(other.mp_window, nullptr))
    , m_width(std::exchange(other.m_width, 0))
    , m_height(std::exchange(other.m_height, 0))
    , m_x(std::exchange(other.m_x, 0))
    , m_y(std::exchange(other.m_y, 0))
    , m_title(std::exchange(other.m_title, NULL))
{
}
WindowGl& WindowGl::operator=(WindowGl&& other)
{
    std::swap(mp_window, other.mp_window);
    std::swap(m_width, other.m_width);
    std::swap(m_height, other.m_height);
    std::swap(m_x, other.m_x);
    std::swap(m_y, other.m_y);
    std::swap(m_title, other.m_title);
    return *this;
}

int WindowGl::getWidth() const
{
    return m_width;
}
int WindowGl::getHeight() const
{
    return m_height;
}
int WindowGl::getX() const
{
    int x;
    glfwGetWindowPos(mp_window, &x, NULL);
    return x;
}
int WindowGl::getY() const
{
    int y;
    glfwGetWindowPos(mp_window, NULL, &y);
    return y;
}

std::string WindowGl::getTitle() const
{
    return m_title;
}
void WindowGl::swapBuffer()
{
    // Back Buffer and Front Buffer
    // Back Buffer - The Buffer that will be edited
    // Front Buffer - The buffer that is shown to the person

    // there is visual buffer and a editing buffer, this will switch the buffer to
    // visual buffer
    glfwSwapBuffers(mp_window);
}

void WindowGl::viewPortArea(int x, int y, int width, int height)
{
    // glViewport(0, 0, 800, 800);
    glViewport(x, y, width, height);
}

void WindowGl::makeContextCurrent()
{
    glfwMakeContextCurrent(mp_window);
}

bool WindowGl::windowShouldClose()
{
    return glfwWindowShouldClose(mp_window);
}

WindowGl::~WindowGl()
{
    glfwDestroyWindow(mp_window);
    glfwTerminate();
}
}; // namespace GlLibrary

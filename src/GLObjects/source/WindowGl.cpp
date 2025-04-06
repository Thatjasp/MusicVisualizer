#include "WindowGl.h"
#include <GLFW/glfw3.h>

#include <iostream>
namespace GlLibrary {

WindowGl::WindowGl(int width, int height, std::string title,
    GLFWmonitor* monitor, GLFWwindow* share)
{
    // Initialize GL Window
    glfwInit();

    // Type Hints for Glfw to understand what version it should use
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    mp_window = glfwCreateWindow(800, 800, "Bruhhhh", NULL, NULL);

    // If window isn't made then terminate
    if (mp_window == NULL) {
        glfwTerminate();
        return;
    }
    makeContextCurrent();
    // init glew
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Wack" << std::endl;
        glfwTerminate();
    }
}

WindowGl::WindowGl(const WindowGl& other)
    : m_width(other.getWidth())
    , m_height(other.getHeight())
    , m_title(other.getTitle())
{
    if (!glfwInit()) {
        // probably return error
        return;
    }
    glfwDestroyWindow(mp_window);

    mp_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);

    glfwSetWindowPos(mp_window, other.getX(), other.getY());
}

WindowGl& WindowGl::operator=(const WindowGl& other)
{
    glfwInit();
    glfwDestroyWindow(mp_window);

    glfwSetWindowPos(mp_window, other.getX(), other.getY());

    return *this;
}

int WindowGl::getWidth() const { return m_width; }
int WindowGl::getHeight() const { return m_height; }
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

std::string WindowGl::getTitle() const { return m_title; }
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

void WindowGl::makeContextCurrent() { glfwMakeContextCurrent(mp_window); }

bool WindowGl::windowShouldClose() { return glfwWindowShouldClose(mp_window); }

WindowGl::~WindowGl()
{
    glfwDestroyWindow(mp_window);
    glfwTerminate();
}
}; // namespace GlLibrary

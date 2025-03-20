#include "WindowGl.h"

namespace GlLibrary {

WindowGl::WindowGl(int width, int height, std::string title,
                   GLFWmonitor *monitor, GLFWwindow *share) {
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
  // Load Glad module
  gladLoadGL();
}

WindowGl::WindowGl(const WindowGl &other)
    : m_width(other.getWidth()), m_height(other.getHeight()) {}
int WindowGl::getWidth() const { return m_width; }
int WindowGl::getHeight() const { return m_height; }

std::string WindowGl::getTitle() const { return m_title; }
void WindowGl::swapBuffer() {
  // Back Buffer and Front Buffer
  // Back Buffer - The Buffer that will be edited
  // Front Buffer - The buffer that is shown to the person

  // there is visual buffer and a editing buffer, this will switch the buffer to
  // visual buffer
  glfwSwapBuffers(mp_window);
}

void WindowGl::viewPortArea(int x, int y, int width, int height) {
  // glViewport(0, 0, 800, 800);
  glViewport(x, y, width, height);
}

void WindowGl::makeContextCurrent() { glfwMakeContextCurrent(mp_window); }

bool WindowGl::windowShouldClose() { return glfwWindowShouldClose(mp_window); }

WindowGl::~WindowGl() {
  glfwDestroyWindow(mp_window);
  glfwTerminate();
}
}; // namespace GlLibrary

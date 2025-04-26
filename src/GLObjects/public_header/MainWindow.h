#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#endif
#include "WindowGl.h"
#include <memory>
#include <string>

class MainWindow {
public:
    // TODO: Rule of 5
    MainWindow(int width, int height, std::string title,
        GLFWmonitor* monitor = NULL, GLFWwindow* share = NULL);

    ~MainWindow();

private:
    std::unique_ptr<GlLibrary::WindowGl> mp_windowGl;
};

#endif

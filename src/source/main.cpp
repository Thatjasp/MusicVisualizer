#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#endif
#include "MainWindow.h"
#include <math.h>
#include <memory>

int main()
{
    auto f = std::make_unique<MainWindow>(800, 800, "Bruhhhh");
    return 0;
}

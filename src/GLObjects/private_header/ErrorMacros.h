#ifndef ERROR_MACROS_H
#define ERROR_MACROS_H

#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#endif
#include <iostream>
#include <signal.h>

#define ASSERT(x) \
    if (!x)       \
    raise(SIGTRAP)

#define GlCall(x)   \
    GlClearError(); \
    x;              \
    GlLogCall(#x, __FILE__, __LINE__);

static void GlClearError()
{
    while (GLenum error = glGetError()) { }
}

static bool GlLogCall(const char* funcName, const char* fileName, int lineNum)
{
    bool noError = true;
    while (GLenum error = glGetError()) {
        std::cerr << "OpenGl Error (" << error << ")\n Function Name: " << funcName << "\n File Name: " << fileName << "\n Line Number: " << lineNum << std::endl;
        // TODO: I don't really like this kind of logic, potentially
        // find a better way so noError doesn't have to give false everytime
        // should be fine for now though
        noError = false;
    }
    return noError;
}

#endif

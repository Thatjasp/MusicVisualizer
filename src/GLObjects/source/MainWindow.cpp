#include "MainWindow.h"
#include "FragmentShader.h"
#include "ShaderProgram.h"
#include "VertexShader.h"
#include "WindowGl.h"
#include <iostream>
#include <math.h>
// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";
// Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
                                   "}\n\0";
MainWindow::MainWindow(int width, int height, std::string title,
    GLFWmonitor* monitor, GLFWwindow* share)
{
    // clang-format off
    GLfloat vertices[] = {
        -0.5, -0.5f * float(std::sqrt(3)) / 3, 0.0f,
        0.5,  -0.5f * float(std::sqrt(3)) / 3, 0.0f,
        0.5,  0.5f * float(std::sqrt(3)) / 3,  0.0f,
    };
    // clang-format on

    mp_windowGl = std::make_unique<GlLibrary::WindowGl>(width, height, title);

    mp_windowGl->viewPortArea(0, 0, 800, 800);

    GlLibrary::ShaderProgram shaderProgram;

    // Reference to Shader
    //    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    {
        GlLibrary::VertexShader vertexShader;
        GlLibrary::FragmentShader fragmentShader;

        vertexShader.addShaderSource(std::string(vertexShaderSource));
        vertexShader.compileShader();

        fragmentShader.addShaderSource(std::string(fragmentShaderSource));
        fragmentShader.compileShader();

        shaderProgram.attachShader(vertexShader);
        shaderProgram.attachShader(fragmentShader);

        shaderProgram.linkShader();
    }

    float positions[6] = {
        -0.5f, -0.5f,
        0.0f, 0.5f,
        0.5f, -0.5f
    };
    // Buffers in OpenGL are just buffers with bytes we specify
    GLuint bufferId;
    // this will get you n ids for n number of buffers
    glGenBuffers(1, &bufferId);
    // In opengl IDs are used to call any type of "Object"

    // this will tell opengl to choose this specific buffer
    glBindBuffer(GL_ARRAY_BUFFER, bufferId);

    // Reserve memory in Buffer, you will need to specify bytes.
    // using manual calculation due to working with stack and heap arrays
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

    // We have to tell OpenGl our layout

    while (!mp_windowGl->windowShouldClose()) {
        glClear(GL_COLOR_BUFFER_BIT);

        mp_windowGl->swapBuffer();

        glfwPollEvents();
    }
    //    // vertex buffer object
    //    GLuint VBO;
    //
    //    // vertex array object | has references to VBOs
    //    // VAOs have metadata about the vertexBufferObjects,
    //    GLuint VAO;
    //
    //    // Generate where the Vector array object will be on the heap
    //    glGenVertexArrays(1, &VAO);
    //    // Generates the buffe for the vertex buffer object
    //    glGenBuffers(1, &VBO);
    //    // Bind, This will assign the target
    //    glBindVertexArray(VAO);
    //
    //    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //
    //    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //
    //    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //    glEnableVertexAttribArray(0);
    //
    //    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //    glBindVertexArray(0);
    //
    //    // there is visual buffer and a editing buffer, this will switch the buffer to
    //    // visual buffer
    //    mp_windowGl->swapBuffer();
    //
    //    while (!mp_windowGl->windowShouldClose()) {
    //        // Color we want to change
    //        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    //        // Cleans the Back buffer and assigns the color to the back buffer
    //        glClear(GL_COLOR_BUFFER_BIT);
    //        glUseProgram(shaderProgram.shaderProgramId());
    //        glBindVertexArray(VAO);
    //        glDrawArrays(GL_TRIANGLES, 0, 3);
    //        mp_windowGl->swapBuffer();
    //
    //        glfwPollEvents();
    //    }
    //
    //    glDeleteVertexArrays(1, &VAO);
    //    glDeleteBuffers(1, &VBO);
}

MainWindow::~MainWindow() { }

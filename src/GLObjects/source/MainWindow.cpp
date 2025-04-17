#include "MainWindow.h"
#include "FragmentShader.h"
#include "Shader.h"
#include "ShaderManager.h"
#include "ShaderProgram.h"
#include "VertexShader.h"
#include "WindowGl.h"
#include <math.h>
// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec4 position;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = position;\n"
                                 "}";
// Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
                                   "layout(location = 0) out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(0.8f, 0.0f, 0.00f, 1.0f);\n"
                                   "}\n";
MainWindow::MainWindow(int width, int height, std::string title,
    GLFWmonitor* monitor, GLFWwindow* share)
{
    mp_windowGl = std::make_unique<GlLibrary::WindowGl>(width, height, title);

    mp_windowGl->viewPortArea(0, 0, 800, 800);

    GlLibrary::ShaderProgram shaderProgram;

    // Reference to Shader
    //    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    {
        //        GlLibrary::VertexShader vertexShader;
        //       GlLibrary::FragmentShader fragmentShader;

        //      fragmentShader.addShaderSource(std::string(fragmentShaderSource));
        //     fragmentShader.compileShader();

        //    vertexShader.addShaderSource(std::string(vertexShaderSource));
        //   vertexShader.compileShader();
        GlLibrary::ShaderManager shaderManager;
        shaderManager.importShaders("build/Debug/res/shader/fragment.glsl");

        shaderManager.compileShaders();

        shaderProgram.attachShader(shaderManager.getFragmentShader());
        shaderProgram.attachShader(shaderManager.getVertexShader());

        shaderProgram.linkShader();
        shaderProgram.validateProgram();
    }
    // clang-format off
    GLfloat positions[8] = { 
        -0.5f, -0.5f, // 0
        0.5f, 0.5f, // 1
        0.5f, -0.5f, // 2
        -0.5f, 0.5f// 3
    };
    // clang-format on

    // Buffers in OpenGL are just buffers with bytes we specify
    GLuint bufferId;
    // this will get you n ids for n number of buffers
    glGenBuffers(1, &bufferId);

    // In opengl IDs are used to call any type of "Object"

    // this will tell opengl to choose this specific buffer
    glBindBuffer(GL_ARRAY_BUFFER, bufferId);

    // Reserve memory in Buffer, you will need to specify bytes.
    // using manual calculation due to working with stack and heap arrays
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), positions, GL_STATIC_DRAW);

    // Args,
    // Index - what is the index of this Vertex Attribute
    // 0 - it is the first attribute
    //
    // Size - How many of the specified types are there in this attribute
    // 2 - Attribute is a position in 2D
    //
    // Type - Type of data in this attribute
    // GL_FLOAT - we have floats in this pointer
    //
    // Normalize - depending on the attribute, we can normalize and convert it
    // into a float this is necessary if you use some kind of int GL_FALSE - don't
    // need to since already float
    //
    // Stride - the size of the Vertex
    // sizeof(float) * 2 - currently our vertex is only a 2d position
    // so we would just say it's 2 floats big
    //
    //
    // Pointer - the offset of attribute from the start of the Vertex
    // 0 - it's the only attribute so theres no offset
    //
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, 0);
    // This will enable the Vertex Attribute we want, it must be done so anything
    // shows up
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    unsigned int indices[] = {
        0, 1, 2,
        0, 1, 3
    };
    // ibo - indexBufferObject
    GLuint ibo;
    glGenBuffers(1, &ibo);

    // ELEMENT ARRAY BUFFER
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, indices, GL_STATIC_DRAW);

    shaderProgram.useProgram();

    while (!mp_windowGl->windowShouldClose()) {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
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
    //    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
    //    GL_STATIC_DRAW);
    //
    //    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
    //    (void*)0); glEnableVertexAttribArray(0);
    //
    //    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //    glBindVertexArray(0);
    //
    //    // there is visual buffer and a editing buffer, this will switch the
    //    buffer to
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

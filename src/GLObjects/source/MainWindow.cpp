#include "MainWindow.h"
#include "IndexBuffer.h"
#include "Renderer.h"
#include "ShaderManager.h"
#include "ShaderProgram.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "WindowGl.h"
#include <math.h>

MainWindow::MainWindow(int width, int height, std::string title,
    GLFWmonitor* monitor, GLFWwindow* share)
{
    mp_windowGl = std::make_unique<GlLibrary::WindowGl>(width, height, title);

    mp_windowGl->viewPortArea(0, 0, 800, 800);

    GlLibrary::ShaderProgram shaderProgram;

    {
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
    // GLuint bufferId;
    // this will get you n ids for n number of buffers
    // glGenBuffers(1, &bufferId);
    //
    //    // In opengl IDs are used to call any type of "Object"
    //
    // this will tell opengl to choose this specific buffer
    // glBindBuffer(GL_ARRAY_BUFFER, bufferId);
    GlLibrary::VertexArray vertexArray;

    // Reserve memory in Buffer, you will need to specify bytes.
    // using manual calculation due to working with stack and heap arrays
    GlLibrary::VertexBuffer vertexBuffer(positions, 8 * sizeof(float));
    vertexBuffer.Bind();
    GlLibrary::VertexBufferLayout bufferLayout;
    bufferLayout.addVertexAttribParams<float>(2);

    vertexArray.addBuffer(vertexBuffer, bufferLayout);
    // glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), positions, GL_STATIC_DRAW);

    // Specifiying the layout will connect our buffer and Vertex Array together

    // Attrib Index, Size of Type, Normalize, Stride, Offset of the First Component
    // Stride - the offset between each of specified vertex attribute
    // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, 0);

    // This will enable the Vertex Attribute we want, it must be done so anything
    // shows up
    // vertexArray.enableAttribute(0);
    // glEnableVertexAttribArray(0);

    unsigned int indices[] = {
        0, 1, 2,
        0, 1, 3
    };

    GlLibrary::IndexBuffer indexBuffer(indices, 6);
    indexBuffer.Bind();

    // ibo - indexBufferObject
    // GLuint ibo;
    // glGenBuffers(1, &ibo);

    // // ELEMENT ARRAY BUFFER
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, indices, GL_STATIC_DRAW);

    shaderProgram.useProgram();

    shaderProgram.addUniformLocation("u_Color");

    float red = 0.05f;
    float increment = 0.05f;

    // Unbind to use example of changing state in while loop
    // glBindVertexArray(0);
    // glUseProgram(0);

    //   indexBuffer.Unbind();
    //  vertexBuffer.Unbind();
    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    GlLibrary::Renderer renderer;
    while (!mp_windowGl->windowShouldClose()) {
        // Bind Shader
        renderer.Clear();
        shaderProgram.useProgram();
        shaderProgram.setUniformLocation4f("u_Color", red, .2f, .4f, 1.0f);
        renderer.Draw(vertexArray, indexBuffer, shaderProgram);
        // Bind Vertex Array Object, this will set up our layout
        //        vertexArray.Bind();
        // Bind Index Buffer
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

        //       GlCall(glDrawElements(GL_TRIANGLES, indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr));
        if (red > 1.0f) {
            increment = -0.05;
        } else if (red < 0.0f) {
            increment = 0.05;
        }
        red += increment;

        mp_windowGl->swapBuffer();

        glfwPollEvents();
    }
}

MainWindow::~MainWindow() { }

#include "MainWindow.h"
#include "WindowGl.h"
#include <math.h>
// Vertex Shader source code
const char *vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
// Fragment Shader source code
const char *fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
    "}\n\0";
MainWindow::MainWindow(int width, int height, std::string title,
                       GLFWmonitor *monitor, GLFWwindow *share) {
  GLfloat vertices[] = {
      -0.5, -0.5f * float(std::sqrt(3)) / 3, 0.0f,
      0.5,  -0.5f * float(std::sqrt(3)) / 3, 0.0f,
      0.5,  0.5f * float(std::sqrt(3)) / 3,  0.0f,
  };

  mp_windowGl = std::make_unique<GlLibrary::WindowGl>(width, height, title);

  // area that we want opengl to render
  glViewport(0, 0, 800, 800);

  // Reference to Shader
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

  // Adds the Shader source to the Vertex Shader
  // Gluint shaderId, Glsizei num of files, char** array of source text, int*
  // size of respective text
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

  // Compiles The shader
  glCompileShader(vertexShader);

  // Reference to fragmentShader
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  // Adds Shader source code to fragment Shader
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

  // Compiles the fragment Shader
  glCompileShader(fragmentShader);

  // Shader program that the GPU will used to create the shaders
  GLuint shaderProgram = glCreateProgram();

  // Attaches the shaders code to the shaderProgram
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);

  // Links shader program to the ma
  glLinkProgram(shaderProgram);

  // executable is made so no need to have shaders
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  // vertex buffer object
  GLuint VBO;

  // vertex array object | has references to VBOs
  // VAOs have metadata about the vertexBufferObjects,
  GLuint VAO;

  // Generate where the Vector array object will be on the heap
  glGenVertexArrays(1, &VAO);
  // Generates the buffe for the vertex buffer object
  glGenBuffers(1, &VBO);
  // Bind, This will assign the target
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  // there is visual buffer and a editing buffer, this will switch the buffer to
  // visual buffer
  mp_windowGl->swapBuffer();

  while (!mp_windowGl->windowShouldClose()) {
    // Color we want to change
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    // Cleans the Back buffer and assigns the color to the back buffer
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    mp_windowGl->swapBuffer();

    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteProgram(shaderProgram);
}

MainWindow::~MainWindow() {}

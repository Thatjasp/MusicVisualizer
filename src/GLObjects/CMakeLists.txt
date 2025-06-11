cmake_minimum_required(VERSION  3.31.5)
project(GLObjects)
find_package(glfw3 REQUIRED)
find_package(glew REQUIRED)
find_package(stb REQUIRED)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PRIVATE_HEADER_FILES
	./private_header/ErrorMacros.h
)
set(PUBLIC_HEADER_FILES 
	#./public_header/VAO.h
	#./public_header/VBO.h
	./public_header/VertexBuffer.h
	./public_header/Renderer.h
	./public_header/VertexBufferLayout.h
	./public_header/VertexArray.h
	./public_header/IndexBuffer.h
	./public_header/Texture.h
	./public_header/WindowGl.h
	./public_header/MainWindow.h
	./public_header/VertexShader.h
	./public_header/ShaderProgram.h
	./public_header/ShaderManager.h
	./public_header/Shader.h
	./public_header/FragmentShader.h
)

set(${PROJECT_NAME}_SOURCE_FILES 
	./source/VertexBuffer.cpp
	./source/IndexBuffer.cpp
	./source/MainWindow.cpp
	./source/WindowGl.cpp
	./source/VertexShader.cpp
	./source/VertexArray.cpp
	./source/VertexBufferLayout.cpp
	./source/Shader.cpp
	./source/Renderer.cpp
	./source/Texture.cpp
	./source/FragmentShader.cpp
	./source/ShaderManager.cpp
	./source/ShaderProgram.cpp)

add_library(${PROJECT_NAME} STATIC ${PUBLIC_HEADER_FILES} ${${PROJECT_NAME}_SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ./public_header/ PRIVATE ./private_header/)

target_link_libraries(${PROJECT_NAME} glfw GLEW::GLEW stb::stb)

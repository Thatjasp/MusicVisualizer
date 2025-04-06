cmake_minimum_required(VERSION  3.31.5)
project(GLObjects)
find_package(glfw3 REQUIRED)
find_package(glad REQUIRED)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PUBLIC_HEADER_FILES 
	#./public_header/VAO.h
	#./public_header/VBO.h
	./public_header/WindowGl.h
	./public_header/MainWindow.h
	./public_header/VertexShader.h
	./public_header/ShaderProgram.h
	./public_header/Shader.h
	./public_header/FragmentShader.h
)

set(${PROJECT_NAME}_SOURCE_FILES 
	./source/MainWindow.cpp
	./source/WindowGl.cpp
	./source/VertexShader.cpp
	./source/Shader.cpp
	./source/FragmentShader.cpp
	./source/ShaderProgram.cpp)

add_library(${PROJECT_NAME} STATIC ${PUBLIC_HEADER_FILES} ${${PROJECT_NAME}_SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ./public_header/)

target_link_libraries(${PROJECT_NAME} glfw glad::glad)

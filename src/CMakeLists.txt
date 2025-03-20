cmake_minimum_required(VERSION  3.31.5)
project(MusicVisualizer)
find_package(glfw3 REQUIRED)
find_package(glad REQUIRED)


add_subdirectory(GLObjects)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXECUTABLE_SUFFIX ".bin")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


set(${PROJECT_NAME}_SOURCE_FILES ./source/main.cpp)

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} glfw opengl::opengl glad::glad GLObjects)


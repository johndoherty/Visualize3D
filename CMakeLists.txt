cmake_minimum_required(VERSION 3.1)
project(Visualize3D)

# The version number.
set (VERSION_MAJOR 1)
set (VERSION_MINOR 0)
 
# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/Config.h.in"
  "${PROJECT_BINARY_DIR}/Config.h"
  )
 
include_directories("${PROJECT_BINARY_DIR}")

# C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# OpenGL
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${GLEW_INCLUDE_DIRS})

add_executable(Visualize3D main.cpp Utils.cpp)
target_link_libraries(Visualize3D glfw)
target_link_libraries(Visualize3D ${OPENGL_gl_LIBRARY})
target_link_libraries(Visualize3D ${GLEW_LIBRARIES})
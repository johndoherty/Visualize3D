cmake_minimum_required(VERSION 3.1)
project(Visualize3D)

# OpenGL
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

find_package(GLM QUIET)
if (!GLM_FOUND)
	set(GLM_INCLUDE_DIRS "/usr/include/glm/")
	message(WARNING "Unable to find glm. Setting include path to ${GLM_INCLUDE_DIRS}.")
endif(!GLM_FOUND)

set(SOURCE Utils.cpp Renderer.cpp ModelBuffers.cpp)
set(SHADERS shaders/FragmentShader.glsl shaders/VertexShader.glsl)

add_library(visualize3d ${SOURCE} ${SHADERS})

target_include_directories(visualize3d PUBLIC ../include)
target_include_directories(visualize3d PRIVATE ${GLEW_INCLUDE_DIRS})
target_include_directories(visualize3d PRIVATE ${GLM_INCLUDE_DIRS})

target_link_libraries(visualize3d PRIVATE glfw)
target_link_libraries(visualize3d PRIVATE ${OPENGL_gl_LIBRARY})
target_link_libraries(visualize3d PRIVATE ${GLEW_LIBRARIES})

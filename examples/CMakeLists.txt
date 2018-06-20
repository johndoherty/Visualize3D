cmake_minimum_required(VERSION 3.1)
project(Visualize3D)

add_executable(cube cube.cpp)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

target_link_libraries(cube visualize3d)
target_link_libraries(cube Threads::Threads)

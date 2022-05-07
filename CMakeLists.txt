cmake_minimum_required(VERSION 3.10)

project(wolf3d VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_compile_options(-Wall -Wextra -pedantic -Os -s -std=c++11)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB SOURCES src/*.cpp)
add_executable(wolf3d ${SOURCES})

find_package(SFML 2.5.1 COMPONENTS graphics system window REQUIRED)
set(OpenGL_GL_PREFERENCE LEGACY)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
target_link_libraries(wolf3d sfml-audio sfml-graphics sfml-system sfml-window GL GLEW)
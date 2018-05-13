cmake_minimum_required(VERSION 3.10)
project(wireframe C)

set(CMAKE_C_STANDARD_REQUIRED 90)

add_executable(fdf "")

#include(app/CMakeLists.txt)
include(sdl_gui/CMakeLists.txt)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_LIST_DIR})

install(TARGETS fdf
        DESTINATION bin)

cmake_minimum_required(VERSION 3.10)
project(wireframe C)

set(CMAKE_C_STANDARD_REQUIRED 90)
#set(CMAKE_VERBOSE_MAKEFILE 1)

add_executable(fdf "")

include(libft/CMakeLists.txt)

include(core/CMakeLists.txt)

include(sdl_gui/CMakeLists.txt)

target_link_libraries(fdf ft)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_LIST_DIR})

install(TARGETS fdf
        DESTINATION bin)

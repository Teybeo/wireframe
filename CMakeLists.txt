cmake_minimum_required(VERSION 3.9)
project(wireframe C)

set(CMAKE_C_STANDARD_REQUIRED 90)
#set(CMAKE_VERBOSE_MAKEFILE 1)

# Set warnings globally
add_compile_options(-Wall -Wextra)

option(USE_ASAN "Enable ASAN (Unix only)" ON)
if (USE_ASAN)
    message("ASAN Enabled")
    # Set flags for ASAN globally
    add_compile_options(-fsanitize=address -g3)
    link_libraries(-fsanitize=address)
endif()

add_executable(fdf "")

include(libft/CMakeLists.txt)
include(core/CMakeLists.txt)
include(sdl_gui/CMakeLists.txt)

target_link_libraries(fdf ft)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_LIST_DIR})

install(TARGETS fdf
        DESTINATION bin)

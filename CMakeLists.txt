cmake_minimum_required(VERSION 3.9)
project(wireframe C)

set(CMAKE_C_STANDARD_REQUIRED 90)
#set(CMAKE_VERBOSE_MAKEFILE 1)

# Set warnings globally
add_compile_options(-Wall -Wextra)

set(GuiBackend "mlx" CACHE STRING "Backend to use for windowing and events" FORCE)
set_property(CACHE GuiBackend PROPERTY STRINGS sdl mlx)

option(USE_ASAN "Enable ASAN (Unix only)" ON)
message(STATUS "AddressSanitizer: ${USE_ASAN}")

if (USE_ASAN)
    # Set flags for ASAN globally
    add_compile_options(-fsanitize=address -g3)
    link_libraries(-fsanitize=address)
endif()

add_executable(fdf "")

include(libft/CMakeLists.txt)
include(core/CMakeLists.txt)

if (GuiBackend STREQUAL sdl)
    include(sdl_gui/CMakeLists.txt)
elseif(GuiBackend STREQUAL mlx)
    include(mlx_gui/CMakeLists.txt)
else()
    message(error "Unrecognized backend name")
endif()

message(STATUS "Backend: ${GuiBackend}")

target_link_libraries(fdf ft)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_LIST_DIR})

install(TARGETS fdf
        DESTINATION bin)

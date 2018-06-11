cmake_minimum_required(VERSION 3.9)
project(wireframe C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_VERBOSE_MAKEFILE 1)

# Set warnings globally
add_compile_options(-Wall -Wextra -pedantic -Wno-comment -Rpass=inline -g3)
add_compile_options(-flto)

set(CMAKE_C_FLAGS_DEBUG  "-g3")
set(CMAKE_C_FLAGS_RELEASE "-g3 -flto")

# Backend to use for windowing and events"
set(GuiBackend "MLX")
#set(GuiBackend "SDL")

option(USE_ASAN "Enable ASAN (Unix only)" OFF)

# On Windows, Force SDL and disable Asan
if (CMAKE_SYSTEM_NAME MATCHES Windows)
    set(GuiBackend SDL)
    set(USE_ASAN OFF)
endif()

message(STATUS "AddressSanitizer: ${USE_ASAN}")
message(STATUS "Backend: ${GuiBackend}")

if (USE_ASAN)
    # Set flags for ASAN globally
    add_compile_options(-fsanitize=address -g3)
    link_libraries(-fsanitize=address)
endif()

add_executable(fdf "")

include(libft/CMakeLists.txt)
include(core/CMakeLists.txt)

if (GuiBackend STREQUAL SDL)
    include(sdl_gui/CMakeLists.txt)
elseif(GuiBackend STREQUAL MLX)
    include(mlx_gui/CMakeLists.txt)
else()
    message(error "Unrecognized backend name")
endif()


target_link_libraries(fdf ft)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_LIST_DIR})

install(TARGETS fdf
        DESTINATION bin)

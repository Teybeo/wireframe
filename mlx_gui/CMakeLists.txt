target_sources(fdf PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/main.c"
        "${CMAKE_CURRENT_LIST_DIR}/mlx_gui.c"
        "${CMAKE_CURRENT_LIST_DIR}/mlx_keyboard.c"
        )
set(libpath "${CMAKE_CURRENT_LIST_DIR}/../minilibx_macos/")
find_library(MLX_LIB mlx PATHS ${libpath} NO_DEFAULT_PATH)
target_include_directories(fdf PUBLIC ${libpath})
#set(MLX_LIB ../minilibx_macos/libmlx.a)

#find_library(MLX_LIB mlx)

target_link_libraries(fdf ${MLX_LIB})
target_link_libraries(fdf "-framework OpenGL -framework AppKit")
target_link_libraries(fdf core)

message(STATUS "MLX lib: ${MLX_LIB}")
message(STATUS "MLX lib: ${libpath}")
